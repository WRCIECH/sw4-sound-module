#include <iostream>
#include <cstdlib>

#include <RtAudio.h>
#include <FilterAdapters.h>
#include <Fir.h>
#include <Noise.h>
#include <SineWave.h>
#include <FileWvOut.h>
#include "FileLoop.h"

using namespace stk;

class FormatWave
{
public:
    FormatWave(float value):
    if_fir(value),
    lpf(value),
    hpf(value)
    {
        std::vector<double> coeffs{
101325, 101325, 101325, 101325, 101325, 101325, 101325, 101325, 101325, 101325, 101325, 101325, 101325, 101325, 101325, 
101325, 101325, 101325, 101326, 101326, 101327, 101327, 101328, 101329, 101330, 101332, 101334, 101336, 101339, 101342, 
101346, 101350, 101355, 101361, 101367, 101373, 101380, 101388, 101396, 101404, 101412, 101420, 101428, 101436, 101443, 
101449, 101454, 101457, 101459, 101459, 101457, 101454, 101448, 101441, 101432, 101422, 101410, 101397, 101384, 101369, 
101354, 101338, 101323, 101308, 101294, 101280, 101266, 101253, 101241, 101229, 101219, 101210, 101202, 101195, 101190, 
};
        double p_def = 101325;
        double p_max = 123756;

        for (auto& a : coeffs)
        {
            a = (a-p_def)/(p_max-p_def);
            std::cout << a  << std::endl;
        }
        fir.setCoefficients(coeffs);
    }

    ~FormatWave(){}
    void open_file(std::string file_name)
    {
        input.openFile(file_name);
    }

    stk::StkFloat tick()
    {
        if (!if_fir)
        {
            return input.tick();
        }
        return fir.tick(input.tick());
        //return input.tick();
    }
private:
    stk::Fir fir;
    FilterAdapters::LowPassFilter lpf;
    FilterAdapters::HighPassFilter hpf;
    FileLoop input;
    int if_fir;
};
int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void *dataPointer)
{
	FormatWave* pF = (FormatWave*)dataPointer;

	StkFloat* samples = (StkFloat*)outputBuffer;

	for (unsigned int i = 0; i < nBufferFrames; i++)
		*samples++ = pF->tick();
	return 0;
}

int main(int argc, char* argv[])
{
    Stk::setSampleRate(44100.0);

    if (argc != 3)
    {
        std::cout << "Podaj nazwę pliku i value!\n";
        return -1;
    }
    std::string file_name(argv[1]);
    float cutoff(atof(argv[2]));

    FormatWave fw(cutoff);
    fw.open_file(file_name);

    // Set the global sample rate before creating class instances.
    RtAudio dac;

    //FileLoop input;
    //input.openFile( "koko.wav");

    /*
    FileWvOut output;
    // Open a 16-bit, one-channel WAV formatted output file
    output.openFile( "liczem.wav", 1, FileWrite::FILE_WAV, Stk::STK_SINT16 );
    //input.setFrequency( 4100.0 );
    // Run the oscillator for 40000 samples, writing to the output file
    for ( int i=0; i<400000; i++ )
    {
        output.tick( lpf.tick(input.tick()) );
    }
    */

	// Figure out how many bytes in an StkFloat and setup the RtAudio stream.
	RtAudio::StreamParameters parameters;
	parameters.deviceId = 6; //dac.getDefaultOutputDevice();
	parameters.nChannels = 1;
	RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = RT_BUFFER_SIZE;
	try
	{
		dac.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&fw);
	}
	catch (RtAudioError &error)
	{
		error.printMessage();
		return -1;
	}
	try
        {
		dac.startStream();
	}
	catch (RtAudioError &error)
	{
		error.printMessage();
		return -1;
	}

    for(;;)
        ;

	// Shut down the output stream.
	try
	{
		dac.closeStream();
	}
	catch (RtAudioError &error)
	{
		error.printMessage();
	}

    return 0;
}

