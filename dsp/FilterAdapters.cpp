#include <Stk.h>
#include "FilterAdapters.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace FilterAdapters
{

LowPassFilter::LowPassFilter(StkFloat threshold):
stk::OnePole()
{
	setCutoffFrequency(threshold);
}

StkFloat LowPassFilter::tick(StkFloat val) 
{ 
	return stk::OnePole::tick(val); 
}

void LowPassFilter::setCutoffFrequency(StkFloat cutoff_frequency) 
{ 
	double pole = 0.0;
	pole = exp(-2.0*M_PI*cutoff_frequency / Stk::sampleRate());
	this->setPole(pole);
}

HighPassFilter::HighPassFilter(StkFloat threshold):
stk::OnePole()
{
	setCutoffFrequency(threshold);
}

StkFloat HighPassFilter::tick(StkFloat val) 
{
	return stk::OnePole::tick(val); 
}

void HighPassFilter::setCutoffFrequency(StkFloat cutoff_frequency) 
{
	double pole = 0.0;
	pole = -exp(-2.0*M_PI*cutoff_frequency / Stk::sampleRate());
	this->setPole(pole);
}

BandPassFilter::BandPassFilter(StkFloat center_freq, StkFloat Q)
{
    setResonance(center_freq, Q, true);
}

VC_Filter::VC_Filter(StkFloat center_freq, StkFloat Q):
Q(Q)
{
    setResonance(center_freq, Q, true);
}

StkFloat VC_Filter::tick(StkFloat val, StkFloat center_freq)
{
    setResonance(center_freq, Q, true);
    return BiQuad::tick(val);
}

DelayLine::DelayLine(StkFloat delay_mili, StkFloat max_delay_mili):
Delay(0.001*delay_mili*Stk::sampleRate(), 0.001*max_delay_mili*Stk::sampleRate())
{

}

}
