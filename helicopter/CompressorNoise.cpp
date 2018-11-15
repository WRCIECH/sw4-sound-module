#include <iostream>
#include <fstream>
#include <algorithm>
#include <CompressorNoise.h>
#include <OneThirdOctaveBand.h>


CompressorNoiseComponent::CompressorNoiseComponent():
G(),
a(),
M_t(-1),
k(-1),
delta(-1.0),
j(-1),
K(-1),
b(-1),
M_m(-1),
r_s_dim(-1),
f_b(-1)
{
}

void CompressorNoiseComponent::setInput(CompressorInput* ci)
{
    input = ci;
    update();

}

void CompressorNoiseComponent::update()
{
    M_t = M_PI*input->N_dim;
    delta = M_t/std::abs(1.0-double(input->V)/double(input->B));

    delta>1.05 ? j=1 : j=2;
    input->s_dim<=1.0 ? k=1 : k=2;

    r_s_dim = input->r_s/sqrt(input->A_e);
    f_b = input->N_dim*input->B*input->c_inf/(input->d_dim*sqrt(input->A_e));
    M_m = std::max(1.0, input->M_d);
}

double CompressorNoiseComponent::compute_mean_square_pressure(double f, double theta, double phi)
{
    double eta = (1.0-input->M_inf*cos(theta))*f/f_b;

    double result = input->A_dim*power_dim()/(4.0*M_PI*r_s_dim*r_s_dim);
    result *= D(theta) * S(eta) / pow(1.0-input->M_inf*cos(theta), 4.0);

    //result = result*input->rho_inf*input->rho_inf*pow(input->c_inf, 4.0);
    return result;
}

double CompressorNoiseComponent::power_dim()
{
    double M_x = input->m_dot_dim/input->A_dim;
    double M_r = sqrt(M_t*M_t + M_x*M_x);
    return K * G(input->i-1, j-1) * pow(input->s_dim, -a(k-1,input->l-1)) * pow(M_m, b)
        * (input->m_dot_dim*input->A_dim)*input->delta_T_dim*input->delta_T_dim*F(M_r, M_m);
}

void CompressorNoiseComponent::print_all_values()
{
    std::cout << "*****************Input****************************\n";
    std::cout << "A_e: " << input->A_e << std::endl;
    //std::cout << "N_e: " << input->N_e << std::endl;
    std::cout << "r_s: " << input->r_s << std::endl;
    std::cout << "A_dim: " << input->A_dim << std::endl;
    std::cout << "B: " << input->B << std::endl;
    std::cout << "d_dim: " << input->d_dim << std::endl;
    std::cout << "i: " << input->i << std::endl;
    std::cout << "M_d: " << input->M_d << std::endl;
    std::cout << "l: " << input->l << std::endl;
    std::cout << "s_dim: " << input->s_dim << std::endl;
    std::cout << "V: " << input->V << std::endl;
    std::cout << "m_dot_dim: " << input->m_dot_dim << std::endl;
    std::cout << "N_dim: " << input->N_dim << std::endl;
    std::cout << "delta_T_dim: " << input->delta_T_dim << std::endl;
    std::cout << "c_inf: " << input->c_inf << std::endl;
    std::cout << "M_inf: " << input->M_inf << std::endl;
    std::cout << "rho_inf: " << input->rho_inf << std::endl;
    std::cout << "\n\n*****************Calculated****************************\n";
    std::cout << "G: " << G << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "M_t: " << M_t << std::endl;
    std::cout << "k: " << k << std::endl;
    std::cout << "delta: " << delta << std::endl;
    std::cout << "j: " << j << std::endl;
    std::cout << "K: " << K << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "M_m: " << M_m << std::endl;
    std::cout << "r_s_dim: " << r_s_dim << std::endl;
    std::cout << "f_b: " << f_b << std::endl;
    std::cout << std::endl << std::endl;
}

InletBroadbandNoise::InletBroadbandNoise()
{
    G(0,0) = 1.0;
    G(0,1) = 1.0;
    G(1,0) = 1.0;
    G(1,1) = 1.0;

    a(0,0) = 0.5;
    a(0,1) = 0.5;
    a(1,0) = 0.5;
    a(1,1) = 0.0;

    K = 1.552/10000;
    b = 2.0;
}

InletBroadbandNoise::~InletBroadbandNoise()
{
}

double InletBroadbandNoise::D(double theta)
{
    return pow(10.0, 0.43);
}

double InletBroadbandNoise::S(double eta)
{
    double sigma = 2.2; //geometric mean deviation
    double result = 0.116*exp(-0.5*(std::log(eta/2.5)/std::log(sigma))*(std::log(eta/2.5)/std::log(sigma)));
    return result;
}

double InletBroadbandNoise::F(double Mr, double Mm)
{
    if (Mr <= 0.9)
        return 1.0;
    else
        return 0.81/Mr/Mr;
}

FrequencySPLPairs InletBroadbandNoise::get_1_3_octave_frequency_spl_vector()
{
    FrequencySPLPairs fvp;

    OneThirdOctaveBand otob;
    auto cf = otob.get_center_frequencies();

    for(auto& f : cf)
    {
        //double current_f = 1000.0*pow(2.0, double(i)/3.0);
        double mean = compute_mean_square_pressure(f, input->theta, input->phi);
        double spl = convert_mean_square_pressure_to_SPL(mean, input->rho_inf, input->c_inf);
        fvp.emplace_back(f, spl);
    }

    return fvp;
}

//Inlet Rotor-Stator Interaction Tones
InletRotorStatorInteractionTones::InletRotorStatorInteractionTones()
{
    G(0,0) = 1.0;
    G(0,1) = 0.580;
    G(1,0) = 0.625;
    G(1,1) = 0.205;

    a(0,0) = 1.0;
    a(0,1) = 1.0;
    a(1,0) = 1.0;
    a(1,1) = 0.0;
    K = 2.683/10000;
    b = 2.0;
}

InletRotorStatorInteractionTones::~InletRotorStatorInteractionTones()
{
}

double InletRotorStatorInteractionTones::D(double theta)
{
    //std::cout << "D(theta) niedoimplementowane!\n";
    return pow(10.0, 0.3);
}

double InletRotorStatorInteractionTones::S(double eta)
{
    Eigen::Matrix2d S_n1;
    S_n1(0,0) = 0.499;
    S_n1(0,1) = 0.136;
    S_n1(1,0) = 0.799;
    S_n1(1,1) = 0.387;
    Eigen::Matrix2d S_nx;
    S_nx(0,0) = 0.250;
    S_nx(0,1) = 0.432;
    S_nx(1,0) = 0.101;
    S_nx(1,1) = 0.307;
    S_nx *= pow(10.0, -0.3*(eta-2));
    if (eta == 1)
    {
        return S_n1(input->i-1, j-1);
    }
    else
    {
        return S_nx(input->i-1, j-1);
    }
}

double InletRotorStatorInteractionTones::F(double Mr, double Mm)
{
    if(Mr <= 0.72)
    {
        return 0.397*pow(Mm,-2.31);
    }
    else if(Mr> 0.72 && Mr<=0.866*pow(Mm, 0.462))
    {
        return 2.053*pow(Mm,-2.31)*pow(Mr,5.0);
    }
    else
    {
        return 0.315*pow(Mm,3.69)*pow(Mr,-8.0);
    }
}

FrequencySPLPairs InletRotorStatorInteractionTones::get_frequency_spl_tones_vector()
{
    FrequencySPLPairs result;
    double current_f = f_b;
    while (current_f < 22050.0)
    {
        double mean = compute_mean_square_pressure(current_f, input->theta, input->phi);
        double spl = convert_mean_square_pressure_to_SPL(mean, input->rho_inf, input->c_inf);
        result.emplace_back(current_f, spl);
        current_f += f_b;

    }
    return result;
}

//Inlet Flow Distortion Tones
InletFlowDistortionTones::InletFlowDistortionTones()
{
    G(0,0) = 1.0;
    G(0,1) = 1.0;
    G(1,0) = 1.0;
    G(1,1) = 1.0;

    a(0,0) = 1.0;
    a(0,1) = 1.0;
    a(1,0) = 1.0;
    a(1,1) = 0.0;

    K = 1.448*0.0001;
    b = 4.31;
}

InletFlowDistortionTones::~InletFlowDistortionTones()
{
}

double InletFlowDistortionTones::D(double theta)
{
    //std::cout << "D(theta) niedoimplementowane!\n";
    return pow(10.0, 0.3);
}

double InletFlowDistortionTones::S(double eta)
{
    return 9.0*pow(10.0, -eta);
}

double InletFlowDistortionTones::F(double Mr, double Mm)
{
    if(Mr <= 0.72)
    {
        return 0.397*pow(Mm,-2.31);
    }
    else if(Mr> 0.72 && Mr<=0.866*pow(Mm, 0.462))
    {
        return 2.053*pow(Mm,-2.31)*pow(Mr,5.0);
    }
    else
    {
        return 0.315*pow(Mm,3.69)*pow(Mr,-8.0);
    }
}

FrequencySPLPairs InletFlowDistortionTones::get_frequency_spl_tones_vector()
{
    FrequencySPLPairs result;
    double current_f = f_b;
    while (current_f < 22050.0)
    {
        double mean = compute_mean_square_pressure(current_f, input->theta, input->phi);
        double spl = convert_mean_square_pressure_to_SPL(mean, input->rho_inf, input->c_inf);
        result.emplace_back(current_f, spl);
        current_f += f_b;

    }
    return result;
}

//Combination Tone Noise
CombinationToneNoise::CombinationToneNoise()
{
    G(0,0) = 1.0;
    G(0,1) = 1.0;
    G(1,0) = 0.316;
    G(1,1) = 0.316;

    a(0,0) = 0.0;
    a(0,1) = 0.0;
    a(1,0) = 0.0;
    a(1,1) = 0.0;
    //K = 6.225*0.0001;
    b = 0.0;
}

CombinationToneNoise::~CombinationToneNoise()
{
}

double CombinationToneNoise::D(double theta)
{
    //std::cout << "D(theta) niedoimplementowane!\n";
    return pow(10.0, -0.43);
}

double CombinationToneNoise::S(double eta)
{
    if (harmonic_type == 0) // 1/8 fundamental combination tone noise
    {
        if(eta <= 0.125)
        {
            return 0.405*pow(8.0*eta, 5.0);
        }
        else
        {
            return 0.405*pow(8.0*eta, -3.0);
        }
    }
    else if (harmonic_type == 1) // 1/4 fundamental combination tone noise
    {
        if(eta <= 0.25)
        {
            return 0.520*pow(4.0*eta, 5.0);
        }
        else
        {
            return 0.520*pow(4.0*eta, -5.0);
        }
    }
    else // 1/2 fundamental combination tone noise
    {
        if(eta <= 0.5)
        {
            return 0.332*pow(2.0*eta, 3.0);
        }
        else
        {
            return 0.332*pow(2.0*eta, -3.0);
        }
    }
}

double CombinationToneNoise::F(double Mr, double Mm)
{
    if (harmonic_type == 0) // 1/8 fundamental combination tone noise
    {
        if(Mr < 1.0)
        {
            return 0.0;
        }
        else if(1 <= Mr && Mr <= 1.61)
        {
            return pow(10.0, -6.75*(1.61-Mr));
        }
        else
        {
            return pow(10.0, -1.21*(Mr-1.61));
        }
    }
    else if (harmonic_type == 1) // 1/4 fundamental combination tone noise
    {
        if(Mr < 1.0)
        {
            return 0.0;
        }
        else if(1 <= Mr && Mr <= 1.322)
        {
            return pow(10.0, -14.75*(1.322-Mr));
        }
        else
        {
            return pow(10.0, -1.33*(Mr-1.322));
        }
    }
    else // 1/2 fundamental combination tone noise
    {
        if(Mr < 1.0)
        {
            return 0.0;
        }
        else if(1 <= Mr && Mr <= 1.146)
        {
            return pow(10.0, -31.85*(1.146-Mr));
        }
        else
        {
            return pow(10.0, -1.41*(Mr-1.146));
        }
    }
}

FrequencySPLPairs CombinationToneNoise::get_frequency_spl_tones_vector()
{
    double k_comb[3];
    k_comb[0] = 6.109*0.0001; //lub 6.225 ???
    k_comb[1] = 2.03*0.001;
    k_comb[2] = 2.525*0.001;
    double harmonic_types[3];
    harmonic_types[0] = 0;
    harmonic_types[1] = 1;
    harmonic_types[2] = 2;

    FrequencySPLPairs result;
    double current_f[3];
    current_f[0] = f_b/8.0;
    current_f[1] = f_b/4.0;
    current_f[2] = f_b/2.0;

    for (int harm=0; harm < 3; ++harm)
    {
        K = k_comb[harm];
        harmonic_type = harmonic_types[harm];

        double mean = compute_mean_square_pressure(current_f[harm], input->theta, input->phi);
        double spl = convert_mean_square_pressure_to_SPL(mean, input->rho_inf, input->c_inf);
        result.emplace_back(current_f[harm], spl);
    }
    return result;
}

//Discharge Broadband Noise
DischargeBroadbandNoise::DischargeBroadbandNoise()
{
    G(0,0) = 1.0;
    G(0,1) = 1.0;
    G(1,0) = 2.0;
    G(1,1) = 2.0;

    a(0,0) = 0.5;
    a(0,1) = 0.5;
    a(1,0) = 0.5;
    a(1,1) = 0.0;

    K = 3.206/10000;
    b = 2.0;
}

DischargeBroadbandNoise::~DischargeBroadbandNoise()
{
}

double DischargeBroadbandNoise::D(double theta)
{
    return pow(10.0, -3.7);
}

double DischargeBroadbandNoise::S(double eta)
{
    double sigma = 2.2; //geometric mean deviation
    double result = 0.116*exp(-0.5*(std::log(eta/2.5)/std::log(sigma))*(std::log(eta/2.5)/std::log(sigma)));
    return result;
}

double DischargeBroadbandNoise::F(double Mr, double Mm)
{
    if (Mr <= 1.0)
        return 1.0;
    else
        return pow(Mr, -2.0);
}

FrequencySPLPairs DischargeBroadbandNoise::get_1_3_octave_frequency_spl_vector()
{
    FrequencySPLPairs fvp;

    OneThirdOctaveBand otob;
    auto cf = otob.get_center_frequencies();

    for(auto& f : cf)
    {
        //double current_f = 1000.0*pow(2.0, double(i)/3.0);
        double mean = compute_mean_square_pressure(f, input->theta, input->phi);
        double spl = convert_mean_square_pressure_to_SPL(mean, input->rho_inf, input->c_inf);
        fvp.emplace_back(f, spl);
    }

    return fvp;
}

//Discharge Rotor-Stator Interaction Tones
DischargeRotorStatorInteractionTones::DischargeRotorStatorInteractionTones()
{
    G(0,0) = 1.0;
    G(0,1) = 0.580;
    G(1,0) = 2.5;
    G(1,1) = 0.820;

    a(0,0) = 1.0;
    a(0,1) = 1.0;
    a(1,0) = 1.0;
    a(1,1) = 0.0;
    K = 2.643/10000;
    b = 2.0;
}

DischargeRotorStatorInteractionTones::~DischargeRotorStatorInteractionTones()
{
}

double DischargeRotorStatorInteractionTones::D(double theta)
{
    //std::cout << "D(theta) niedoimplementowane!\n";
    return pow(10.0, -3.45);
}

double DischargeRotorStatorInteractionTones::S(double eta)
{
    Eigen::Matrix2d S_n1;
    S_n1(0,0) = 0.499;
    S_n1(0,1) = 0.136;
    S_n1(1,0) = 0.799;
    S_n1(1,1) = 0.387;
    Eigen::Matrix2d S_nx;
    S_nx(0,0) = 0.250;
    S_nx(0,1) = 0.432;
    S_nx(1,0) = 0.101;
    S_nx(1,1) = 0.307;
    S_nx *= pow(10.0, -0.3*(eta-2));
    if (eta == 1)
    {
        return S_n1(input->i-1, j-1);
    }
    else
    {
        return S_nx(input->i-1, j-1);
    }
}

double DischargeRotorStatorInteractionTones::F(double Mr, double Mm)
{
    if (Mr <= 1.0)
        return 1.0;
    else
        return pow(Mr, -2.0);
}

FrequencySPLPairs DischargeRotorStatorInteractionTones::get_frequency_spl_tones_vector()
{
    FrequencySPLPairs result;
    double current_f = f_b;
    while (current_f < 22050.0)
    {
        double mean = compute_mean_square_pressure(current_f, input->theta, input->phi);
        double spl = convert_mean_square_pressure_to_SPL(mean, input->rho_inf, input->c_inf);
        result.emplace_back(current_f, spl);
        current_f += f_b;

    }
    return result;
}
