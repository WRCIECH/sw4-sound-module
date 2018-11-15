#include "SourceNoise.h"

int get_lowest_harmonic(double eta)
{
    double n_ld;
    double one_third_oct = pow(10.0, -1.0/20.0)*eta;
    double fractpart = modf(one_third_oct, &n_ld);

    return int(n_ld)+1;
}

int get_highest_harmonic(double eta)
{
    double n_ld;
    double one_third_oct = pow(10.0, 1.0/20.0)*eta;
    double fractpart = modf(one_third_oct, &n_ld);

    return int(n_ld);
}

double convert_mean_square_pressure_to_SPL(double mean_pressure, double rho_inf, double c_inf)
{
    double p_ref = 2.0*0.00001;

    return 10.0 * log10(mean_pressure) + 20.0* log10((rho_inf*c_inf*c_inf)/p_ref);
    //return 20*log10(mean_pressure/p_ref);
}

double convert_p_rms_to_SPL(double p_rms)
{
    double p_ref = 2.0*0.00001;

    return 20.0 * log10(p_rms/p_ref);
}

SourceNoise::SourceNoise()
{
}

SourceNoise::~SourceNoise()
{
}

void SourceNoise::setMinimumHearableSPL(double dB_min, double min_vol)
{
    dB_min_volume = dB_min;
    min_volume = min_vol;
}

double SourceNoise::getVolumeForSPL(double SPL)
{
    double diff = SPL - dB_min_volume;
    double rest = double(diff/3.0);

    return min_volume*pow(2.0, rest);
}

