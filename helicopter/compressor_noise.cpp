#include <iostream>
#include <RtAudio.h>
#include <FilterAdapters.h>
#include <SineWave.h>
#include "SFML/Network.hpp"
#include <CompressorNoise.h>
#include <TonalAndBroadbandNoise.h>


using namespace stk;

std::string ip_address;
int ip_port;

class CompressorNoiseAudio
{
public:
    CompressorNoiseAudio()
    {
        ci.A_e = M_PI/4.0; //engine reference, m^2
        //ci.N_e = 1; //number of engines
        ci.r_s = 1.0; //distance from source to observer, m
        ci.theta = 0.0; // polar directivity angle, deg
        ci.phi = 0.0; // azimuthal directivity angle, deg

        //Fan Geometry
        ci.A_dim = 1.0; //fan inlet cross-sectional area, re A_e
        ci.B = 20; //number of rotor blades
        ci.d_dim = 1.128; //fan rotor diameter, re sqrt(A_e)
        ci.i = 1; //inlet guide vane index
        ci.M_d = 1.0; //fan rotor relative tip Mach number at design point
        ci.l = 1; //inlet flow distortion index
        ci.s_dim = 1.0; //rotor-stator spacing, re C (C = mean rotor blade chord, m)
        ci.V = 50; //number of stator vanes

        //Fan Noise Parameters
        ci.m_dot_dim = 0.2; //mass flow rate, re rho_inf*c_inf*A_e
        ci.N_dim = 0.3; //rotational speed, re c_inf/d
        ci.delta_T_dim = 0.2; //total temperature rise across fan, re T_inf

        //Ambient conditions
        ci.c_inf = 340.294; //ambient speed of sound, m/s
        ci.M_inf = 0.0; //aircraft Mach number
        ci.rho_inf = 1.225; // ambient density, kg/m^3

        ibn.setInput(&ci);
        irsit.setInput(&ci);
        ifdt.setInput(&ci);
        ctn.setInput(&ci);
        drsit.setInput(&ci);
        dbn.setInput(&ci);

        ibn.setMinimumHearableSPL(98.0, 0.0001);
        irsit.setMinimumHearableSPL(98.0, 0.0001);
        ifdt.setMinimumHearableSPL(98.0, 0.0001);
        ctn.setMinimumHearableSPL(98.0, 0.0001);
        drsit.setMinimumHearableSPL(98.0, 0.0001);
        dbn.setMinimumHearableSPL(98.0, 0.0001);

        tonal_irsit.set(&irsit);
        br_ibn.set(&ibn);
        tonal_ifdt.set(&ifdt);
        tonal_ctn.set(&ctn);
        tonal_drsit.set(&drsit);
        br_dbn.set(&dbn);
    }
    ~CompressorNoiseAudio(){}

    stk::StkFloat tick()
    {
        stk::StkFloat result = 0;
        result += tonal_irsit.tick();
        result += br_ibn.tick();
        result += tonal_ifdt.tick();
        result += tonal_ctn.tick();

        result += tonal_drsit.tick();
        //result += br_dbn.tick();
        return  result;
    }
    void update()
    {
        /*
        std::cout << "Update: "
        << " A_e: " << ci.A_e
        << ", rs: " << ci.r_s
        << ", theta: " << ci.theta
        << ", phi: " << ci.phi
        << ", Adim: " << ci.A_dim
        << ", B: " << ci.B
        << ", d_dim: " << ci.d_dim
        << ", i: " << ci.i
        << ", M_d: " << ci.M_d
        << ", l: " << ci.l
        << ", s_dim: " << ci.s_dim
        << ", V: " << ci.V
        << ", m_dot_dim: " << ci.m_dot_dim
        << ", N_dim: " << ci.N_dim
        << ", dT: " << ci.delta_T_dim
        << ", c_inf: " << ci.c_inf
        << ", M_inf: " << ci.M_inf
        << ", rho_inf: " << ci.rho_inf;
        std::cout << std::endl;
        */

        std::cout << "Compressor noise : before update\n";
        tonal_irsit.update();
        br_ibn.update();
        tonal_ifdt.update();
        tonal_ctn.update();
        tonal_drsit.update();
        br_dbn.update();
        std::cout << "Compressor noise : after update\n";
    }


    CompressorInput ci;
private:
    TonalNoise<InletRotorStatorInteractionTones> tonal_irsit;
    BroadbandNoise<InletBroadbandNoise> br_ibn;

    TonalNoise<InletFlowDistortionTones> tonal_ifdt;
    TonalNoise<CombinationToneNoise> tonal_ctn;

    TonalNoise<DischargeRotorStatorInteractionTones> tonal_drsit;
    BroadbandNoise<DischargeBroadbandNoise> br_dbn;

    InletRotorStatorInteractionTones irsit;
    InletBroadbandNoise ibn;
    InletFlowDistortionTones ifdt;
    CombinationToneNoise ctn;
    DischargeRotorStatorInteractionTones drsit;
    DischargeBroadbandNoise dbn;

};

int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void *dataPointer)
{
	CompressorNoiseAudio* pF = (CompressorNoiseAudio*)dataPointer;
	StkFloat *samples = (StkFloat *)outputBuffer;

	for (unsigned int i = 0; i < nBufferFrames; i++)
		*samples++ = pF->tick();
	return 0;
}

void run(CompressorNoiseAudio& jn)
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

    while (1)
    {
        if (sock.receive(&jn.ci, sizeof(jn.ci), received, ip, inPort))
        {
            std::cout << "Blad odbioru" << std::endl;
        }
        else
        {
            std::cout << "Odebrano pakied udp rho_inf: " << jn.ci.rho_inf << std::endl;
            jn.update();
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

	CompressorNoiseAudio jn;
    jn.update();
	run(jn);

	return 0;
}
