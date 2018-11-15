#include <iostream>
#include <fstream>
#include <RotationalNoise.h>


RotationalNoise::RotationalNoise()
{
}

RotationalNoise::~RotationalNoise()
{
}

void RotationalNoise::update()
{
    M = input->V/input->c;
    beta = sqrt(1.0-M*M);
    calculate_thrust_and_torque_radially();
}

double RotationalNoise::get_frequency(int m)
{
    return (m+1)*input->Omega*input->B/(2.0*M_PI);
}

double RotationalNoise::get_omega(int m)
{
    return (m+1)*input->Omega*input->B;
}

double RotationalNoise::p_Magliozzi(int m)
{
    double omega = get_omega(m);
    double k = omega/input->c;
    double n = input->Omega/(2.0*M_PI);

    double theta = M_PI/4.0; //!!!!!!!!!!!!!

    double dr ((input->R_end-input->R_begin)/input->r_size*input->R);

    double dpsi = 2.0*M_PI/input->psi_size;

    cdouble integral_sum;
    for (int i=1; i <= input->r_size; ++i)
    {
        double r = ((input->R_end-input->R_begin)/input->r_size*i+input->R_begin)*input->R;

        cdouble theta_element = 0;
        double dC_T = input->B*A[i-1]/(input->rho*n*n*pow(input->R*2.0, 4));
        for(int j=1; j <= input->psi_size/2; ++j) //????????
        {
            double psi=M_PI/input->psi_size*2.0*j-M_PI/input->psi_size;
            double S = sqrt(input->X*input->X + beta*beta*(input->Y*input->Y-2.0*input->Y*r*cos(psi)+r*r));
            double sigma = (M*input->X+S)/(beta*beta);

            double dC_P = input->B*r*2.0*M_PI*F[i-1]/(input->rho*n*n*pow(input->R*2.0, 5));
            //std::cout << F[i-1] << " ";
            cdouble Q = cdouble(input->X/S/S, k*(M+input->X/S)/(1-M*M))*sin(k*sigma) +
                cdouble(k*(M+input->X/S)/(1-M*M), -input->X/S/S)*sin(k*sigma);
            cdouble G(sin(k*sigma), cos(k*sigma));
            theta_element += cos(m*input->B*psi)/S*(-dC_T*Q + m*input->B*2.0*input->R/(2.0*M_PI*r*r)*dC_P*G)*dpsi;
        }
        integral_sum += r/(input->chord*cos(theta))*sin(m*input->B*input->chord*cos(theta)/(2*r))*theta_element*dr;
    }

    cdouble before_integral = input->rho*input->Omega*input->Omega*pow(input->R*2.0, 4.0)/(4.0*pow(M_PI,4.0)*m*input->B);

    return  abs(before_integral*integral_sum);
}

double RotationalNoise::get_p_rms(int m)
{
    return p_Magliozzi(m);
}

FrequencySPLPairs RotationalNoise::get_frequency_spl_tones_vector()
{
    FrequencySPLPairs fvp;

    for (int i = 0; i < input->max_harmonic_number; ++i)
    {
        double frequency = get_frequency(i);

        double p_rms = get_p_rms(i+1);
        //double spl = 124.572 + 20.0*log(p_rms);
        double spl = convert_p_rms_to_SPL(p_rms/sqrt(2));

        //std::cout << "Pressure for harmonic " << i+1 << ": " << p_rms << ", spl: " << spl << std::endl;
        fvp.emplace_back(frequency, spl);
    }


    return fvp;
}

