#include <fstream>
#include <vector>
#include <fftw3.h>
#include "FilterAdapters.h"
#include "Noise.h"
#include "Fir.h"

using namespace stk;
const int NUMBER_OF_SAMPLES = 44100;


void read_coeffs(std::vector<stk::StkFloat>& coeffs, std::string file_name)
{
    std::string line;
    std::ifstream myfile (file_name);
    if (myfile.is_open())
    {
      while ( getline (myfile,line) )
      {
          coeffs.push_back(std::stod(line));
      }
      myfile.close();
    }

    else std::cout << "Unable to open file"; 
}

int main(int argc, char* argv[])
{
    std::cout << argv[1];
    std::string file_name(argv[1]);
    Stk::setSampleRate(44100.0);
    Noise noise;
    FilterAdapters::LowPassFilter fpf(10000);
    FilterAdapters::HighPassFilter hpf(10000);
    std::vector<stk::StkFloat> coeffs;

    read_coeffs(coeffs, file_name);

    stk::Fir band_pass_filter(coeffs);

    std::vector<double> noise_data;
    std::vector<double> lpf_data;
    std::vector<double> hpf_data;
    std::vector<double> band_pass_data;

    std::vector<double> lpf_freq_data;
    std::vector<double> hpf_freq_data;
    std::vector<double> bp_freq_data;

    for ( unsigned int i=0; i<NUMBER_OF_SAMPLES; i++ )
    {
        noise_data.push_back(noise.tick());
        lpf_data.push_back(fpf.tick(noise_data.back()));
        hpf_data.push_back(hpf.tick(noise_data.back()));
        band_pass_data.push_back(band_pass_filter.tick(noise_data.back()));
    }

    int N = NUMBER_OF_SAMPLES;
    fftw_complex *in, *out;
    fftw_plan my_plan;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);

    for (int i = 0; i<N; ++i)
    {
        in[i][0] = lpf_data[i];
        in[i][1] = 0.0;
    }

    my_plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(my_plan);

    for (int i = 0; i<N; ++i)
    {
        lpf_freq_data.push_back(out[i][0]*out[i][0] + out[i][1]*out[i][1]);
    }

    for (int i = 0; i<N; ++i)
    {
        in[i][0] = band_pass_data[i];
        in[i][1] = 0.0;
    }

    fftw_execute(my_plan);

    for (int i = 0; i<N; ++i)
    {
        bp_freq_data.push_back(out[i][0]*out[i][0] + out[i][1]*out[i][1]);
    }

    fftw_destroy_plan(my_plan);
    fftw_free(in);
    fftw_free(out);


    // Zapisywanie danych na plik
    std::ofstream dec;
    dec.open ("fft_decomposition.txt");

    for ( unsigned int i=0; i<NUMBER_OF_SAMPLES/2; i++ )
    {
        dec << i << " " << noise_data[i] << " " << lpf_data[i] << " " << lpf_freq_data[i] << " " << bp_freq_data[i] << std::endl;
    }

    dec.close();

    int col_number = 5;
    std::string name = "band_octave_";
    std::string to_file = std::string(";set term png;set output \\\"diagrams/") + name + std::string(".png\\\"");
    std::string diagram = std::string("gnuplot -p -e \"") + to_file + std::string(";plot 'fft_decomposition.txt' u 1:"); 
    diagram += std::to_string(col_number) + std::string("t \\\"") +  name + std::string("\\\" w lines\"");

    std::string command = diagram;
    std::cout << command << std::endl << std::endl;
    system(command.c_str());

    return 0;
}

