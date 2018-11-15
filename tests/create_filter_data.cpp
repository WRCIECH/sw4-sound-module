#include <fstream>
#include <vector>
#include "FilterAdapters.h"
#include "Noise.h"

using namespace stk;
const int NUMBER_OF_SAMPLES = 44100;

//lop, hip, bp | center_freq | radius | nazwa pliku
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Podaj center frequency i radius!\n";
        return -1;
    }
    double center_freqency = atof(argv[1]);
    double radius = atof(argv[2]);

    std::cout << "FFT decompositions for center: " << center_freqency << " and radius: " << radius << "\n";

    Stk::setSampleRate(44100.0);
    Noise noise;
    FilterAdapters::LowPassFilter fpf(10000);
    FilterAdapters::HighPassFilter hpf(10000);
    //FilterAdapters::BandPassFilter band_pass_filter(500.0, 5.0);
    stk::BiQuad band_pass_filter;
    //frequency, radius, normalize
    //band_pass_filter.setResonance(10000.0, 0.5, true);
    //band_pass_filter.setResonance(10000.0, 0.25, true);
    band_pass_filter.setResonance(center_freqency, radius, true);
    //band_pass_filter.setResonance(10000.0, 0.5, false);

    std::vector<double> noise_data;
    std::vector<double> lpf_data;
    std::vector<double> hpf_data;
    std::vector<double> bp_data;

    for ( unsigned int i=0; i<NUMBER_OF_SAMPLES; i++ )
    {
        noise_data.push_back(noise.tick());
        lpf_data.push_back(fpf.tick(noise_data.back()));
        hpf_data.push_back(hpf.tick(noise_data.back()));
        bp_data.push_back(band_pass_filter.tick(noise_data.back()));
    }

    std::ofstream fout_lpf("low_pass_filter.dat", std::ios::out | std::ios::binary);
    fout_lpf.write((char*)&lpf_data[0], lpf_data.size() * sizeof(double));
    fout_lpf.close();

    std::ofstream fout_hpf("high_pass_filter.dat", std::ios::out | std::ios::binary);
    fout_hpf.write((char*)&hpf_data[0], hpf_data.size() * sizeof(double));
    fout_hpf.close();

    std::ofstream fout_bp("band_pass_filter.dat", std::ios::out | std::ios::binary);
    fout_bp.write((char*)&bp_data[0], bp_data.size() * sizeof(double));
    fout_bp.close();

    return 0;
}

