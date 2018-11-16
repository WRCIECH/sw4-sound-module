//Class based on: http://www.aerodynamics4students.com/propulsion/blade-element-rotor-theory.php

#ifndef BLADE_ELEMENT_MOMENTUM_H
#define  BLADE_ELEMENT_MOMENTUM_H

#include <cmath>
#include <vector>

struct RotationalNoiseInput
{
    double Omega; //angular velocity
    double B; //number of propeller blades
    double c; //velocity of sound
    double rho; //fluid density
    double V; //forward velocity
    double R; //length of propeller blades
    double X; //distance to observer from propeller plane at time sound heard, positive if observer ahead of propeller
    double Y; //distance to observer from propeller axis
    double R_begin; //at which radius blade loading begins
    double R_end; //at which radius blade loading ends

    //To BladeElementMomentum
    double chord; //chord length of blade assumed constant with radius 
    double collective; //collective angle.
    double cyclic; //max cyclic angle.
    double tilt; //tilt
    double Vc; // climb speed
    double vflap; // max flapping velocity

    int r_size; //number of r elements
    int psi_size; //number of circumferential elements
    int max_harmonic_number;
};

class BladeElementMomentum
{
public:
    BladeElementMomentum();
    ~BladeElementMomentum();
    void calculate_thrust_and_torque_radially();
    void setInput(RotationalNoiseInput* p_rni);

protected:
    RotationalNoiseInput* input;
    std::vector<double> A;
    std::vector<double> F;

private:
    double dia; //diameter of the rotor
    double tonc; //thickness to chord ratio for propeller section (constant with radius)
    double rstep; // use 16 blade segments (starting at 20// R (hub) to 95//R)
};

#endif //BLADE_ELEMENT_MOMENTUM_H
