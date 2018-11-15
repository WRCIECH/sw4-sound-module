#include <GearboxNoise.h>



GearboxNoise::GearboxNoise():
engine_speed(91.0),
gear_ratio(14.0),
gear_mix(1.0)
{
    sine1.setFrequency(1.45 * engine_speed*gear_ratio);
    sine2.setFrequency(2.81 * engine_speed*gear_ratio);
    sine3.setFrequency(9.41 * engine_speed*gear_ratio);
}

GearboxNoise::~GearboxNoise()
{
}

stk::StkFloat GearboxNoise::tick() 
{
    sine1.setFrequency(1.45 * engine_speed*gear_ratio);
    sine2.setFrequency(2.81 * engine_speed*gear_ratio);
    sine3.setFrequency(9.41 * engine_speed*gear_ratio);

    StkFloat res1 = sine1.tick();
	StkFloat res2 = sine2.tick();
	StkFloat res3 = sine3.tick();

	return res1*0.2 + res2*0.33 + res3*0.14;

}
