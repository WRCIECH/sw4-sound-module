#include <iostream>
#include <RtAudio.h>
#include <FilterAdapters.h>
#include <SineWave.h>
#include "SFML/Network.hpp"
#include <BladeElementMomentumTheory.h>
#include <RotationalNoise.h>
#include <TonalAndBroadbandNoise.h>

using namespace stk;

std::string ip_address;
int ip_port;

class RotationalNoiseAudio
{
public:
    RotationalNoiseAudio()
    {
        rni.Omega = 400.0/60.0*2.0*M_PI;
        rni.B = 3;
        rni.c = 343.0; //velocity of sound
        rni.rho = 1.2; //fluid density
        rni.V = 0; //forward velocity
        rni.R = 5.0; //length of propeller blades

        rni.X = 1000.0; //distance to observer from propeller plane at time sound heard, 
                      //positive if observer ahead of propeller
        rni.Y = 1.0; //distance to observer from propeller axis

        rni.R_begin = 0.2;
        rni.R_end = 0.95;

        rni.chord = 0.10;
        rni.collective = 8.0/180*M_PI;
        rni.cyclic = 0.0/180*M_PI;
        rni.tilt = 0.0/180.0*M_PI;
        rni.Vc = 0.0;
        rni.vflap = 0.0;

        rni.r_size = 16;
        rni.psi_size = 16;
        rni.max_harmonic_number = 60;

        rn.setInput(&rni);
        rn.update();

        rn.setMinimumHearableSPL(70.0, 0.0001);

        tonal_loading_noise.set(&rn);
    }
    ~RotationalNoiseAudio(){}

    stk::StkFloat tick()
    {
        stk::StkFloat result = 0;
        result += tonal_loading_noise.tick();
        return  result;
    }
    void update()
    {
        tonal_loading_noise.update();
    }

    RotationalNoiseInput rni;
private:
    TonalNoise<RotationalNoise> tonal_loading_noise;
    RotationalNoise rn;
};

int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void *dataPointer)
{
	RotationalNoiseAudio* pF = (RotationalNoiseAudio*)dataPointer;
	StkFloat *samples = (StkFloat *)outputBuffer;

	for (unsigned int i = 0; i < nBufferFrames; i++)
		*samples++ = pF->tick();
	return 0;
}

void run(RotationalNoiseAudio& rn)
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
		dac.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&rn);
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

    char container[100];
    while (1)
    {
        //if (sock.receive(&rn.rni, sizeof(rn.rni), received, ip, inPort))
        if (sock.receive(container, sizeof(100), received, ip, inPort))
        {
            std::cout << "Receive error" << std::endl;
        }
        else
        {
            //????

            auto* pI = (RotationalNoiseInput*) container;
            rn.rni = *pI;

            std::cout << "Udp rho_inf: " << rn.rni.rho << std::endl;
            rn.update();
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
	    ip_port = 7150;
	}
    else
    {
	    ip_address = std::string(argv[1]);
	    ip_port = atoi(argv[2]);
    }


    std::cout << "Address: " << ip_address << ": " << ip_port << std::endl;

	RotationalNoiseAudio rn;
    rn.update();
	run(rn);

	return 0;
}

