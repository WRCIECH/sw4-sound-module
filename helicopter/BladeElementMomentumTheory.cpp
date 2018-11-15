#include <BladeElementMomentumTheory.h>
#include <cstdlib>
#include <iostream>

BladeElementMomentum::BladeElementMomentum()
{
}

BladeElementMomentum::~BladeElementMomentum()
{
}

void BladeElementMomentum::setInput(RotationalNoiseInput* p_rni)
{
    input = p_rni;
}

void BladeElementMomentum::calculate_thrust_and_torque_radially()
{
    dia = 2.0*input->R;
    tonc = 0.12*input->chord;
    rstep = (input->R_end-input->R_begin)/input->r_size*input->R;

    A.clear();
    F.clear();
    for (int i = 1; i <= input->r_size; ++i)
    {
        double rad = ((input->R_end-input->R_begin)/input->r_size*i+input->R_begin)*input->R;
        double DtDr = 0;
        double DqDr = 0;
        for (int j=1; j <= input->psi_size; ++j) //loop over each angular sector
        {
             double psi=M_PI/input->psi_size*2.0*j-M_PI/input->psi_size;
             //calculate local blade element setting angle
             double theta = input->collective+input->cyclic*cos(psi);
             double sigma=2.0*input->chord/2.0/M_PI/rad;
             //guess initial value of induced velocity
             double Vi=10.0;
             //set logical variable to control iteration
             bool finished=false;
             //set iteration count and check flag
             int sum=1;
             int itercheck=0;

             while (!finished)
             {
                 //normal velocity components
                 double V0 = Vi+input->Vc+input->V*sin(input->tilt)+input->vflap*rad*sin(psi);
                 //disk plane velocity
                 double V2 = input->Omega*rad+input->V*cos(input->tilt)*sin(psi);
                 //flow angle
                 double phi = atan2(V0,V2);
                 //blade angle of attack
                 double alpha = theta-phi;
                 //lift coefficient
                 double cl = 6.2*alpha;
                 //drag coefficient
                 double cd = 0.008-0.003*cl+0.01*cl*cl;
                 //local velocity at blade
                 double Vlocal = sqrt(V0*V0+V2*V2);
                 //thrust grading
                 DtDr = 0.5*input->rho*Vlocal*Vlocal*2.0*input->chord*(cl*cos(phi)-cd*sin(phi))/input->psi_size;
                 //torque grading
                 DqDr = 0.5*input->rho*Vlocal*Vlocal*2.0*input->chord*rad*(cd*cos(phi)+cl*sin(phi))/input->psi_size;
                 //momentum check on induced velocity
                 double tem1 = DtDr/(M_PI/4.0*rad*input->rho*V0);
                 //stabilise iteration
                 double Vinew = 0.9*Vi+0.1*tem1;
                 if (Vinew < 0)
                 {
                     Vinew = 0;
                 }
                 //check for convergence
                 if (std::abs(Vinew-Vi)<1.0e-5)
                 {
                     finished = true;
                 }
                 Vi = Vinew;
                 //increment iteration count
                 sum=sum+1;
                 //check to see if iteration stuck
                 if (sum>500)
                 {
                     finished=true;
                     itercheck=1;
                 }
             }
        }
        A.push_back(DtDr*rstep);
        F.push_back(DqDr*rstep);
        //std::cout << "A size: " << A.size() << std::endl;
    }
}
