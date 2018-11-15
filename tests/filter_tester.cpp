#include <iostream>
#include <RtAudio.h>
#include <Noise.h>
#include <FilterAdapters.h>
#include <SFML/Network.hpp>

using namespace stk;
using namespace FilterAdapters;
stk::Noise noise;

typedef LowPassFilter FilterType;
//typedef HighPassFilter FilterType;
//typedef BandPassFilter FilterType;

int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void *dataPointer)
{
	FilterType* pF = (FilterType*)dataPointer;
	StkFloat* samples = (StkFloat*)outputBuffer;

	for (unsigned int i = 0; i < nBufferFrames; i++)
		*samples++ = pF->tick(noise.tick());
	return 0;
}

void run()
{
	// Set the global sample rate before creating class instances.
	Stk::setSampleRate(44100.0);
	RtAudio dac;

	FilterType es(10000);

	// Figure out how many bytes in an StkFloat and setup the RtAudio stream.
	RtAudio::StreamParameters parameters;
	parameters.deviceId = 6; //dac.getDefaultOutputDevice();
	parameters.nChannels = 1;
	RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = RT_BUFFER_SIZE;
	try
	{
		dac.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&es);
	}
	catch (RtAudioError &error)
	{
		error.printMessage();
		return;
	}
	try
	{
		dac.startStream();
	}
	catch (RtAudioError &error)
	{
		error.printMessage();
		return;
	}
	// Block waiting here.
	std::cout << "\nGram ... podaj zero (100, by zakonczyc)\n";
	stk::StkFloat h; h = 0.5;

    sf::UdpSocket sock;
    sf::IpAddress ip("localhost");
    unsigned short inPort = 7150;
    size_t received = 0;

    if (sock.bind(inPort) == sf::Socket::Done)
    {
    	std::cout << "Successfully binded port: " << inPort << std::endl;
    }
    else
    {
        std::cout << "Could not bind port: " << inPort << std::endl;
        char a; std::cin >> a;
        return;
    }

    float val = 100.0;

	while (h < 10.0)
	{
        if (sock.receive(&val, sizeof(float), received, ip, inPort))
        {
            std::cout << "Błąd odbioru" << std::endl;
        }
        std::cout << "Odebrano UDP o wartości: " << val << ", received: " << received << std::endl;

		es.setCutoffFrequency(val);
	}

	// Shut down the output stream.
	try
	{
		dac.closeStream();
	}
	catch (RtAudioError &error)
	{
		error.printMessage();
	}
}

int main()
{
	run();

	std::cout << "Running engine sound...\n";
	return 0;
}
