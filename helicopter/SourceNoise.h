#ifndef SOURCE_NOISE_H
#define SOURCE_NOISE_H

#include <vector>
#include <cmath>

int get_lowest_harmonic(double eta);
int get_highest_harmonic(double eta);

//Shortucts
typedef std::vector<std::pair<double, double>> FrequencySPLPairs;

double convert_mean_square_pressure_to_SPL(double mean_pressure, double rho_inf, double c_inf);
double convert_p_rms_to_SPL(double p_rms);

class SourceNoise
{
public:

    SourceNoise();
    ~SourceNoise();

    void setMinimumHearableSPL(double dB_min, double min_vol);
    double getVolumeForSPL(double SPL);

protected:
    double dB_min_volume;
    double min_volume;

};
#endif //SOURCE_NOISE_H
