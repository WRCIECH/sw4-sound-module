#include <fstream>
#include <vector>
#include <complex>
#include "FilterAdapters.h"
#include "Noise.h"

using namespace stk;
const int NUMBER_OF_SAMPLES = 44100;

class BiquadAdapter : public stk::BiQuad
{
public:
    std::vector<double> get_zeros() {return std::vector<double>{b_[0], b_[1], b_[2]}; };
    std::vector<double> get_poles() {return std::vector<double>{a_[0], a_[1], a_[2]}; };


};

//lop, hip, bp | center_freq | radius | nazwa pliku
int main(int argc, char* argv[])
{
    /*
    if (argc != 4)
    {
        std::cout << "Podaj center frequency, radius i normalizację!\n";
        return -1;
    }
    double center_freqency = atof(argv[1]);
    double radius = atof(argv[2]);
    bool normalize = atof(argv[3]);
    std::cout << "Normalizacja: " << normalize << std::endl;

    std::cout << "FFT decompositions for center: " << center_freqency << " and radius: " << radius << "\n";

    Stk::setSampleRate(44100.0);
    Noise noise;
    BiquadAdapter band_pass_filter;
    //frequency, radius, normalize
    band_pass_filter.setResonance(center_freqency, radius, normalize);

    std::cout << "Dane biquad filter: \n";
    std::cout << "Radius: " << radius << std::endl;
    std::cout << "Center frequency: " << center_freqency << std::endl;
    std::cout << "Gain: " << band_pass_filter.getGain() << std::endl;
    auto b_ = band_pass_filter.get_zeros();
    std::cout << "Zero coeffs: ";
    for (auto& a : b_)
        std::cout << a << ", ";
    std::cout << std::endl;

    auto a_ = band_pass_filter.get_poles();
    std::cout << "Pole coeffs: ";
    for (auto& a : a_)
        std::cout << a << ", ";
    std::cout << std::endl;

    double delta0 = sqrt(b_[1]*b_[1] - 4.0*b_[2]*b_[0]);
    double zero1 = (-b_[1]+delta0)/(2.0*b_[0]);
    double zero2 = (-b_[1]-delta0)/(2.0*b_[0]);

    std::complex<double> deltap = sqrt(std::complex<double>(a_[1]*a_[1] - 4.0*a_[2]*1.0));
    std::complex<double> pole1 = (-a_[1]+deltap)/(2.0*1.0);
    std::complex<double> pole2 = (-a_[1]-deltap)/(2.0*1.0);

    std::cout << "Zeros: " << zero1 << ", " << zero2 << std::endl;
    std::cout << "Poles:\n" << pole1.real() << " + " << pole1.imag() << "i"  << ", " << std::endl;
    std::cout << pole2.real() << " + " << pole2.imag() << "i,"  << std::endl;

    std::vector<double> noise_data;
    std::vector<double> bp_data;

    for ( unsigned int i=0; i<NUMBER_OF_SAMPLES; i++ )
    {
        noise_data.push_back(noise.tick());
        bp_data.push_back(band_pass_filter.tick(noise_data.back()));
    }

    //std::ofstream fout_bp("band_pass_filter.dat", std::ios::out | std::ios::binary);
    //fout_bp.write((char*)&bp_data[0], bp_data.size() * sizeof(double));
    //fout_bp.close();
    */

    Noise noise;
    BiQuad bq;
    //bq.setCoefficients(0.002583945956173948, 0, -0.002583945956173948, 1.9965326405070354, -0.9967321199505188);
    bq.setCoefficients(0.002583945956173948, 0, -0.002583945956173948, -1.9965326405070354, 0.9967321199505188);
    //bq.setCoefficients(0.00434432, 0, -0.00434432, -1.99124994, 0.99131135 );
    for(int i =0; i<5000000; ++i)
    {
        double from_noise = noise.tick();
        double result = bq.tick(from_noise);
        std::cout << from_noise << ", " << result << std::endl;
    }

    return 0;
}
