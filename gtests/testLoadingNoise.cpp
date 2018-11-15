#include<iostream>
#include<vector>
#include<gtest/gtest.h>

#include <RotationalNoise.h>
#include <BladeElementMomentumTheory.h>

class testLoadingNoise: public ::testing::Test
{
protected:
    testLoadingNoise()
    {}
     virtual void SetUp()
     {
         ri.Omega = 400.0/60.0*2.0*M_PI;
         ri.B = 3;
         ri.c = 343.0; //velocity of sound
         ri.rho = 1.2; //fluid density
         ri.V = 0; //forward velocity
         ri.R = 5.0; //length of propeller blades
         ri.X = 1000.0; //distance to observer from propeller plane at time sound heard, 
                      //positive if observer ahead of propeller
         ri.Y = 1.0; //distance to observer from propeller axis

         ri.R_begin = 0.2;
         ri.R_end = 0.95;
         ri.chord = 0.10;
         ri.collective = 8.0/180*M_PI;
         ri.cyclic = 0.0/180*M_PI;
         ri.tilt = 0.0/180.0*M_PI;
         ri.Vc = 0.0;
         ri.vflap = 0.0;
         ri.r_size = 16;
         ri.psi_size = 16;
         ri.max_harmonic_number = 60;

         rn.setInput(&ri);
         rn.update();

         rn.setMinimumHearableSPL(100.0, 0.0001);
     }

     virtual void TearDown()
     {
     }
     RotationalNoiseInput ri;
     RotationalNoise rn;
};

TEST_F(testLoadingNoise, testGetFrequency)
{
    ASSERT_DOUBLE_EQ(rn.get_frequency(0), 3.0*400.0/60.0 );
}

TEST_F(testLoadingNoise, testCalculatingFrequencies)
{
    auto tones = rn.get_frequency_spl_tones_vector();
    ASSERT_EQ(tones.size(), 60);
    ASSERT_DOUBLE_EQ(tones[0].first, 3.0*400.0/60.0 );
    for (auto& a : tones)
    {
        std::cout << a.first << ", " << a.second << std::endl;
    }
}
