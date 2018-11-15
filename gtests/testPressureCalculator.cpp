#include<iostream>
#include<vector>
#include<gtest/gtest.h>

#include <RotationalNoise.h>


TEST(testInputReader, testInputReaderBladeShapes)
{
    SoundInputReader sir;
    sir.SetBladeShapesFromFile("tests/blade_shape_data.dat");

    ASSERT_EQ(sir.shapes.size(), 100);
    ASSERT_EQ(sir.shapes[0].ksi_1, 82);
    ASSERT_EQ(sir.shapes[0].ksi_2, 77);
    ASSERT_EQ(sir.shapes[0].eta_1, 68);
    ASSERT_EQ(sir.shapes[0].eta_2, 80);

    ASSERT_EQ(sir.shapes[99].ksi_1, 60);
    ASSERT_EQ(sir.shapes[99].ksi_2, 86);
    ASSERT_EQ(sir.shapes[99].eta_1, 93);
    ASSERT_EQ(sir.shapes[99].eta_2, 41);

    //sir.SetUserParametersFromFile("test/user_parameters_data.dat");
    //sir.SetFlappingAnglesFromFile("test/flapping_angles_data.dat");
    //sir.SetBladeMotionsFromFile("test/blade_motion_data.dat");
    //sir.SetSurfacePressureFromFile("test/surface_pressure_data.dat");
}

class testRotationalNoiseCalculator: public ::testing::Test
{
protected:
     virtual void SetUp()
     {
         number_of_time_points = 1024;
         Omega = 230.0;
         M_f = 0.5;
         M_h = 0.7;
         alpha_dp = 30.0/180.0*M_PI;

         rnc.set_N_t(number_of_time_points);
         rnc.set_M_f(M_f);
         rnc.set_M_h(M_h);
         rnc.set_alpha_dp(alpha_dp);
         rnc.set_Omega(Omega);
     }

     virtual void TearDown()
     {
     }

     int number_of_time_points;
     double Omega;
     double M_f;
     double M_h;
     double alpha_dp;
     RotationalNoiseCalculator rnc;
};

TEST_F(testRotationalNoiseCalculator, testCalculatingTimeSteps)
{
    rnc.calculate_time_steps();
    ASSERT_DOUBLE_EQ(rnc.get_time(0), 0.0);
    ASSERT_DOUBLE_EQ(rnc.get_time(50), 50.0*2*M_PI/(float(number_of_time_points)*Omega));
}

TEST_F(testRotationalNoiseCalculator, testCalculateHelicopterVelocity)
{
    Eigen::Vector3d velocity(-M_f/M_h*cos(alpha_dp), 0.0, -M_f/M_h*sin(alpha_dp));
    //ASSERT_DOUBLE_EQ(rnc.get_V()[0], velocity[0]);
    //ASSERT_DOUBLE_EQ(rnc.get_V()[1], velocity[1]);
    //ASSERT_DOUBLE_EQ(rnc.get_V()[2], velocity[2]);
}

TEST_F(testRotationalNoiseCalculator, testFirstTauEstimation)
{
    //ASSERT_DOUBLE_EQ(tau, );
}

TEST_F(testRotationalNoiseCalculator, testCalculatingPressure)
{
    rnc.calculate_sound_pressure();
    std::vector<double> pressure_data = rnc.get_sound_pressure();
    ASSERT_EQ(pressure_data.size(), number_of_time_points);
}


