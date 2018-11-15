#ifndef FILTER_ADAPTERS_H
#define FILTER_ADAPTERS_H

#include <Filter.h>
#include <OnePole.h>
#include <Delay.h>
#include <BlitSaw.h>
#include <BiQuad.h>

using stk::StkFloat;

namespace FilterAdapters
{

	template <typename T>
	T clip(const T& n, const T& lower, const T& upper)
	{
		return std::max(lower, std::min(n, upper));
	}

	class LowPassFilter : public stk::OnePole
	{
	public:
		LowPassFilter(StkFloat threshold);
		StkFloat tick(StkFloat val);
		void setCutoffFrequency(StkFloat cutoff_frequency);
	};

	class HighPassFilter : public stk::OnePole
	{
	public:
		HighPassFilter(StkFloat threshold);
		StkFloat tick(StkFloat val);
		void setCutoffFrequency(StkFloat cutoff_frequency);
	};

	class BandPassFilter : public stk::BiQuad
	{
	public:
		BandPassFilter(StkFloat center_freq, StkFloat Q);
	};

    //Voltage Conrolled Band Pass Filter
	class VC_Filter : public stk::BiQuad
	{
	public:
		VC_Filter(StkFloat center_freq, StkFloat Q);
        StkFloat tick(StkFloat val, StkFloat center_freq);
    private:
        StkFloat Q;
	};

	class DelayLine : public stk::Delay
	{
	public:
		DelayLine(StkFloat delay_mili, StkFloat max_delay_mili);
	};
};

#endif //FILTER_ADAPTERS_H

