#include<iostream>
#include<vector>
#include<gtest/gtest.h>

#include <CompressorNoise.h>

class testCompressorNoise: public ::testing::Test
{
protected:
     virtual void SetUp()
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

         irsit.setInput(&ci);
         ibn.setInput(&ci);

         irsit.setMinimumHearableSPL(107.0, 0.0001);
         ibn.setMinimumHearableSPL(107.0, 0.0001);

     }

     virtual void TearDown()
     {
     }
     CompressorInput ci;
     InletRotorStatorInteractionTones irsit;
     InletBroadbandNoise ibn;
};

TEST_F(testCompressorNoise, testInletRotorStatorInteractionTones)
{
    InletRotorStatorInteractionTones irsit;
    irsit.setInput(&ci);

    auto tones = irsit.get_frequency_spl_tones_vector();
    double blade_freq = ci.N_dim*ci.B*ci.c_inf/ci.d_dim/sqrt(ci.A_e);

    ASSERT_EQ(tones.size(), int(44100.0/2.0/blade_freq));
    ASSERT_DOUBLE_EQ(tones[0].first, blade_freq);
    ASSERT_DOUBLE_EQ(tones[1].first, 2.0*blade_freq);
    ASSERT_DOUBLE_EQ(tones[8].first, 9.0*blade_freq);

}

TEST_F(testCompressorNoise, testConversionUtilities)
{
    ASSERT_DOUBLE_EQ(0.0002, irsit.getVolumeForSPL(110.0));
    ASSERT_DOUBLE_EQ(0.0004, irsit.getVolumeForSPL(113.0));

    //ASSERT_DOUBLE_EQ(0.0, convert_mean_square_pressure_to_SPL(2.0*0.00001));
    //ASSERT_DOUBLE_EQ(100.0, convert_mean_square_pressure_to_SPL(2.0));
}

TEST_F(testCompressorNoise, testInletBroadbandNoise)
{
    InletBroadbandNoise ibn;
    ibn.setInput(&ci);

    auto third_octaves = ibn.get_1_3_octave_frequency_spl_vector();
    ASSERT_EQ(30, third_octaves.size());

    ASSERT_DOUBLE_EQ(third_octaves[0].first, 1000.0*pow(2.0, -16.0/3.0));
    ASSERT_DOUBLE_EQ(third_octaves[1].first, 1000.0*pow(2.0, -15.0/3.0));
    ASSERT_DOUBLE_EQ(third_octaves[8].first, 1000.0*pow(2.0, -8.0/3.0));

    //ibn.print_all_values();
    for (auto& a : third_octaves)
    {
        //std::cout << a.first << ", " << a.second << std::endl;
        ASSERT_TRUE(a.second < 200.0);
    }
}

TEST_F(testCompressorNoise, testOutputToSTK)
{
    double blade_freq = ci.N_dim*ci.B*ci.c_inf/ci.d_dim/sqrt(ci.A_e);
    auto tones = irsit.get_frequency_spl_tones_vector();

    ASSERT_EQ(tones.size(), int(44100.0/2.0/blade_freq));
    ASSERT_DOUBLE_EQ(tones[0].first, blade_freq);
    ASSERT_DOUBLE_EQ(tones[1].first, 2.0*blade_freq);
    ASSERT_DOUBLE_EQ(tones[8].first, 9.0*blade_freq);
    for (auto& a : tones)
    {
        ASSERT_TRUE(a.second > 20.0);
        ASSERT_TRUE(a.second < 200.0);
    }
}
