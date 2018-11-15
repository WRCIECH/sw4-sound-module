#include <iostream>
#include <RtAudio.h>
#include <FilterAdapters.h>
#include <GearboxNoise.h>
#include "SFML/Network.hpp"

using namespace stk;

std::string ip_address;
int ip_port;

struct GearboxParams
{
    float engine_speed;
    float gear_ratio;
    float gear_mix;
};

int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void *dataPointer)
{
	GearboxNoise* pF = (GearboxNoise*)dataPointer;
	StkFloat *samples = (StkFloat *)outputBuffer;

	for (unsigned int i = 0; i < nBufferFrames; i++)
		*samples++ = pF->tick();
	return 0;
}

void run(GearboxNoise& jn)
{
	// Set the global sample rate before creating class instances.
	Stk::setSampleRate(44100.0);
	RtAudio dac;

	// Figure out how many bytes in an StkFloat and setup the RtAudio stream.
	RtAudio::StreamParameters parameters;
	parameters.deviceId = 6;//dac.getDefaultOutputDevice();
	parameters.nChannels = 1;
	RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = RT_BUFFER_SIZE;
	try
	{
		dac.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&jn);
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

    sf::UdpSocket sock;
    //sock.setBlocking(false);
    sf::IpAddress ip(ip_address.c_str());
    unsigned short inPort = ip_port;

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

    GearboxParams gp;
    while (1)
    {
        if (sock.receive(&gp, sizeof(gp), received, ip, inPort))
        {
            std::cout << "Blad odbioru" << std::endl;
        }
        else
        {
            std::cout << "Odebrano eng_speed: " << gp.engine_speed << std::endl;
            jn.SetEngineSpeed(gp.engine_speed);
            jn.SetGearRatio(gp.gear_ratio);
            jn.SetGearMix(gp.gear_mix);
        }
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

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Selected default host and port: localhost: 7150\n");
	    ip_address = std::string("localhost");
	    ip_port = 7160;
	}
    else
    {
	    ip_address = std::string(argv[1]);
	    ip_port = atoi(argv[2]);
    }


    std::cout << "Address: " << ip_address << ": " << ip_port << std::endl;
    /*
	std::wstring ip_address_w(argv[1]);
	std::string ip_address(ip_address_w.begin(), ip_address_w.end());
	int ip_port = _wtoi(argv[2]);
    */

	GearboxNoise jn;

	run(jn);

	std::cout << "Running gearbox sound...\n";
	return 0;
}
