#include <vector>
#include <fstream>
#include <SineWave.h>
#include <Noise.h>
#include <BiQuad.h>
#include <OneThirdOctaveBand.h>


template<class T>
class TonalNoise
{
public:
    TonalNoise(){};
    ~TonalNoise(){};

    void set(T* t)
    {
        noise_component = t;
    }

    stk::StkFloat tick()
    {
        double result = 0.0;
        for (int i=0; i<tones.size(); ++i)
        {
            result += volumes[i]*tones[i].tick();
        }
        return result;
    }

    void update()
    {
        noise_component->update();
        auto freq_vol_vec = noise_component->get_frequency_spl_tones_vector();

        tones.resize(freq_vol_vec.size());
        volumes.resize(freq_vol_vec.size());

        //std::cout << "TonalNoise: \n";
        for (int i=0; i<tones.size(); ++i)
        {
            tones[i].setFrequency(freq_vol_vec[i].first);
            volumes[i] = noise_component->getVolumeForSPL(freq_vol_vec[i].second);
            //std::cout << freq_vol_vec[i].first << ", " << freq_vol_vec[i].second << ", " << volumes[i] << std::endl;
        }
    }

    void create_file(std::string file_name)
    {
        std::vector<double> outputs(10000);
        for (auto& a : outputs)
        {
            a = tick();
        }

        std::ofstream fout(file_name, std::ios::out | std::ios::binary);
        fout.write((char*)&outputs[0], outputs.size() * sizeof(double));
        fout.close();
    }
private:
    T* noise_component;
    std::vector<float> volumes;
    std::vector<stk::SineWave> tones;
};

template<class T>
class BroadbandNoise
{
public:
    BroadbandNoise(){};
    ~BroadbandNoise(){};

    void set(T* t)
    {
        noise_component = t;
    }

    stk::StkFloat tick()
    {
        stk::StkFloat result = 0.0;
        for (int i = 0; i < biquads.size(); ++i)
        {
            //std::cout << i << ": " << volumes[i] << std::endl;
            result += volumes[i]*biquads[i].tick(noise.tick());
        }

        return result;
    }

    void update()
    {
        noise_component->update();
        auto band_pressures = noise_component->get_1_3_octave_frequency_spl_vector();

        biquads.resize(band_pressures.size());
        volumes.resize(band_pressures.size());
        auto coeffs = otob.get_coefficients();

        std::cout << "BroadbandNoise: \n";
        for (int i=0; i<band_pressures.size(); ++i)
        {
            biquads[i].setCoefficients(coeffs[i].b0, coeffs[i].b1, coeffs[i].b2, -coeffs[i].a1, -coeffs[i].a2, true); //b0, b1, b2, a1, a2, clearState = false
            volumes[i] = noise_component->getVolumeForSPL(band_pressures[i].second);
            //std::cout << band_pressures[i].first << ", " << band_pressures[i].second << ", " << volumes[i] << std::endl;
        }
    }

    void create_file(std::string file_name)
    {
        std::vector<double> outputs(10000);
        for (auto& a : outputs)
        {
            a = tick();
        }

        std::ofstream fout(file_name, std::ios::out | std::ios::binary);
        fout.write((char*)&outputs[0], outputs.size() * sizeof(double));
        fout.close();
    }
private:
    T* noise_component;
    std::vector<float> volumes;
    std::vector<stk::BiQuad> biquads;
    stk::Noise noise;
    OneThirdOctaveBand otob;
};
