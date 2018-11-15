#include <iostream>
#include <vector>
#include <complex>

struct BiquadCoefficients
{
    BiquadCoefficients(){}
    BiquadCoefficients(double b0,double b1, double b2, double a1, double a2):
        b0(b0), b1(b1), b2(b2), a1(a1), a2(a2)
    {}

    double b0;
    double b1;
    double b2;
    double a1;
    double a2;
};

class OneThirdOctaveBand
{
public:
    OneThirdOctaveBand();
    ~OneThirdOctaveBand();
    std::vector<double> get_center_frequencies();
    std::vector<std::pair<double,double>> get_lower_upper_pairs();
    std::vector<BiquadCoefficients> get_coefficients();
    void print();

private:
    std::vector<double> centres;
    std::vector<std::pair<double,double>> lower_upper_pairs;
    std::vector<BiquadCoefficients> coeffs;
};
