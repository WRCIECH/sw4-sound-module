#ifndef ROTATIONAL_NOISE_H
#define  ROTATIONAL_NOISE_H
#include <vector>
#include <string>
#include <complex>
#include <Eigen/Dense>
#include <SourceNoise.h>
#include <BladeElementMomentumTheory.h>

typedef std::complex<double> cdouble;

class RotationalNoise : public SourceNoise, public BladeElementMomentum
{
public:
    RotationalNoise();
    ~RotationalNoise();

    virtual FrequencySPLPairs get_frequency_spl_tones_vector();

    void update();
    double p_Magliozzi(int m);
    double get_frequency(int m);
    double get_omega(int m);
    double get_p_rms(int m);
private:
    double M;
    double beta;
};
#endif  // ROTATIONAL_NOISE_H
