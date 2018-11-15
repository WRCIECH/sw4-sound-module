#include<iostream>
#include<vector>
#include<gtest/gtest.h>

#include <OneThirdOctaveBand.h>

TEST(testOneThirdOctaveBand, testCenterFreqs)
{
    OneThirdOctaveBand otob;
    auto cf = otob.get_center_frequencies();
    ASSERT_EQ(cf.size(), 30);

    auto l_u_pairs = otob.get_lower_upper_pairs();

    ASSERT_EQ(l_u_pairs.size(), 30);

    otob.print();
}
