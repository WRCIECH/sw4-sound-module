#include <FilterAdapters.h>
#include <SineWave.h>
#include <Noise.h>

using namespace FilterAdapters;

class GearboxNoise
{
public:
    GearboxNoise();
    ~GearboxNoise();
    stk::StkFloat tick();

    void SetEngineSpeed(double new_speed){ engine_speed = new_speed; };
    void SetGearRatio(double new_ratio){ gear_ratio = new_ratio; };
    void SetGearMix(double new_gear_mix){ gear_mix = new_gear_mix; };

private:
    double engine_speed;
    double gear_ratio;
    double gear_mix;

    stk::SineWave sine1;
    stk::SineWave sine2;
    stk::SineWave sine3;
};

