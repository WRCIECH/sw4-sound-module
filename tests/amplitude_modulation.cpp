// crtsine.cpp STK tutorial program
#include "SineWave.h"
#include "RtAudio.h"
#include <SFML/Network.hpp>
using namespace stk;

struct AmplitudeModulator
{
    float A0;
    float A1;
    SineWave s1;
    SineWave s2;
};

struct AmplitudeModulationParameters
{
    float A0;
    float A1;
    float f0;
    float f1;
};

// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples.
int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *dataPointer )
{
  AmplitudeModulator *ampmod = (AmplitudeModulator *) dataPointer;
  float& A0 = ampmod->A0;
  float& A1 = ampmod->A1;
  SineWave& sine1 = ampmod->s1;
  SineWave& sine2 = ampmod->s2;

  register StkFloat *samples = (StkFloat *) outputBuffer;
  for ( unsigned int i=0; i<nBufferFrames; i++ )
    *samples++ = (A0+A1*sine2.tick())*sine1.tick();
  return 0;
}


int main()
{
    // Set the global sample rate before creating class instances.
    Stk::setSampleRate( 44100.0 );
    AmplitudeModulator ampmod;

    SineWave sine;
    RtAudio dac;
    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = 6;//dac.getDefaultOutputDevice();
    parameters.nChannels = 1;
    RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    try {
      dac.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&ampmod );
    }
    catch ( RtAudioError &error ) {
      error.printMessage();
      return 0;
    }

    ampmod.s1.setFrequency(440.0);
    ampmod.s2.setFrequency(440.0);
    sine.setFrequency(440.0);

    try {
      dac.startStream();
    }
    catch ( RtAudioError &error ) {
      error.printMessage();
      return 0;
    }

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
        return 0;
    }

    AmplitudeModulationParameters amp_params;

	while (1)
	{
        if (sock.receive(&amp_params, sizeof(AmplitudeModulationParameters), received, ip, inPort))
        {
            std::cout << "Błąd odbioru" << std::endl;
        }
        std::cout << "Odebrano UDP o wartości: " << amp_params.A0 << ", received: " << received << std::endl;

        ampmod.A0 = amp_params.A0;
        ampmod.A1 = amp_params.A1;
        ampmod.s1.setFrequency(amp_params.f0);
        ampmod.s2.setFrequency(amp_params.f1);
	}

    // Shut down the output stream.
    try {
      dac.closeStream();
    }
    catch ( RtAudioError &error ) {
      error.printMessage();
    }

    return 0;
}


