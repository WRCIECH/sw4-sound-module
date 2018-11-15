#ifndef COMPRESSOR_NOISE_H
#define  COMPRESSOR_NOISE_H
#include <vector>
#include <string>
#include <Eigen/Dense>
#include <SourceNoise.h>

//Inputs
//
struct CompressorInput
{
    double A_e; //engine reference, m^2
    //int N_e; //number of engines
    double r_s; //distance from source to observer, m
    double theta; // polar directivity angle, deg
    double phi; // azimuthal directivity angle, deg

    //Fan Geometry
    double A_dim; //fan inlet cross-sectional area, re A_e
    int B; //number of rotor blades
    double d_dim; //fan rotor diameter, re sqrt(A_e)
    int i; //inlet guide vane index
    double M_d; //fan rotor relative tip Mach number at design point
    int l; //inlet flow distortion index
    double s_dim; //rotor-stator spacing, re C (C = mean rotor blade chord, m)
    int V; //number of stator vanes

    //Fan Noise Parameters
    double m_dot_dim; //mass flow rate, re rho_inf*c_inf*A_e
    double N_dim; //rotational speed, re c_inf/d
    double delta_T_dim; //total temperature rise across fan, re T_inf

    //Ambient conditions
    double c_inf; //ambient speed of sound, m/s
    double M_inf; //aircraft Mach number
    double rho_inf; // ambient density, kg/m^3
};

class CompressorNoiseComponent : public SourceNoise
{
public:
    CompressorNoiseComponent();
    virtual ~CompressorNoiseComponent(){};

    void setInput(CompressorInput* ci);
    void update();
    double compute_mean_square_pressure(double f, double theta, double phi);
    double power_dim();
    virtual double D(double theta) = 0;
    virtual double S(double eta) = 0;
    virtual double F(double Mr, double Mm) = 0;
    //virtual FrequencySPLPairs get_frequency_spl_tones_vector() = 0;
    void print_all_values();
protected:
    Eigen::Matrix2d G;
    Eigen::Matrix2d a;
    double M_t;
    CompressorInput* input;
    int k; //1=s_dim<=1.0, 2= s_dim>1.0
    double delta;
    int j; //1=delta>1.05, 2 else
    double K;
    double b;
    double M_m;
    double r_s_dim;
    double f_b;
};

class InletBroadbandNoise: public CompressorNoiseComponent
{
public:
    InletBroadbandNoise();
    ~InletBroadbandNoise();
    virtual double D(double theta);
    virtual double S(double eta);
    virtual double F(double Mr, double Mm);
    FrequencySPLPairs get_1_3_octave_frequency_spl_vector();
};

class InletRotorStatorInteractionTones: public CompressorNoiseComponent
{
public:
    InletRotorStatorInteractionTones();
    ~InletRotorStatorInteractionTones();
    virtual double D(double theta);
    virtual double S(double eta);
    virtual double F(double Mr, double Mm);
    FrequencySPLPairs get_frequency_spl_tones_vector();
};

class InletFlowDistortionTones: public CompressorNoiseComponent
{
public:
    InletFlowDistortionTones();
    ~InletFlowDistortionTones();
    virtual double D(double theta);
    virtual double S(double eta);
    virtual double F(double Mr, double Mm);
    virtual FrequencySPLPairs get_frequency_spl_tones_vector();
};

class CombinationToneNoise: public CompressorNoiseComponent
{
public:
    CombinationToneNoise();
    ~CombinationToneNoise();
    virtual double D(double theta);
    virtual double S(double eta);
    virtual double F(double Mr, double Mm);
    virtual FrequencySPLPairs get_frequency_spl_tones_vector();
private:
    int harmonic_type;

};

class DischargeBroadbandNoise: public CompressorNoiseComponent
{
public:
    DischargeBroadbandNoise();
    ~DischargeBroadbandNoise();
    virtual double D(double theta);
    virtual double S(double eta);
    virtual double F(double Mr, double Mm);
    FrequencySPLPairs get_1_3_octave_frequency_spl_vector();
};

class DischargeRotorStatorInteractionTones: public CompressorNoiseComponent
{
public:
    DischargeRotorStatorInteractionTones();
    ~DischargeRotorStatorInteractionTones();
    virtual double D(double theta);
    virtual double S(double eta);
    virtual double F(double Mr, double Mm);
    virtual FrequencySPLPairs get_frequency_spl_tones_vector();
};

#endif  // COMPRESSOR_NOISE_H
