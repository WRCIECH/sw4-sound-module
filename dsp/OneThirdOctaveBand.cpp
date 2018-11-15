#include <OneThirdOctaveBand.h>
#include <algorithm>


OneThirdOctaveBand::OneThirdOctaveBand()
{
    for (int i = -16; i <= 13; ++i)
    {
        double current_f = 1000.0*pow(2.0, double(i)/3.0);
        centres.push_back(current_f);
    }

    double fd = pow(2.0, 1.0/6.0);
    for(auto& a : centres)
    {
        lower_upper_pairs.emplace_back(a/fd, a*fd);
    }

    coeffs.resize(30);
    coeffs[0] = BiquadCoefficients(0.0020926921229277753, 0, -0.0020926921229277753, 1.9991628638815513, -0.9991753202119088); //b0, b1, b2, a1, a2
    coeffs[1] = BiquadCoefficients(0.0015405568350019489, 0, -0.0015405568350019489, 1.998949716168712, -0.998969529523203);
    coeffs[2] = BiquadCoefficients(0.0008214047355932585, 0, -0.0008214047355932585, 1.9986703782159898, -0.9987018258463596);
    coeffs[3] = BiquadCoefficients(0.001293035091775888, 0, -0.001293035091775888, 1.9983148449864627, -0.9983647564625312);
    coeffs[4] = BiquadCoefficients(0.0030795453583947314, 0, -0.0030795453583947314, 1.9978608951743075, -0.9979401072816353);
    coeffs[5] = BiquadCoefficients(0.001641734816232337, 0, -0.001641734816232337, 1.9972796900653549, -0.9974053974315534);
    coeffs[6] = BiquadCoefficients(0.002583945956173948, 0, -0.002583945956173948, 1.9965326405070354, -0.9967321199505188);
    coeffs[7] = BiquadCoefficients(0.002139960073714925, 0, -0.002139960073714925, 1.9955679325004336, -0.9958844489898151);
    coeffs[8] = BiquadCoefficients(0.003279215976538762, 0, -0.003279215976538762, 1.9943153463500156, -0.9948175093814291);
    coeffs[9] = BiquadCoefficients(0.003995659131838879, 0, -0.003995659131838879, 1.9926782416391688, -0.9934748216768647);
    coeffs[10] = BiquadCoefficients(0.004271090274293973, 0, -0.004271090274293973, 1.9905224547569225, -0.9917858284922455);
    coeffs[11] = BiquadCoefficients(0.005527810208390605, 0, -0.005527810208390605, 1.9876585161892484, -0.9896617381382705);
    coeffs[12] = BiquadCoefficients(0.0066377668467456925, 0, -0.0066377668467456925, 1.983816586820144, -0.9869919443776932);
    coeffs[13] = BiquadCoefficients(0.008507182820381837, 0, -0.008507182820381837, 1.9786073954114065, -0.9836387012485823);
    coeffs[14] = BiquadCoefficients(0.010514659370469389, 0, -0.010514659370469389, 1.9714888352490716, -0.9794547397591463);
    coeffs[15] = BiquadCoefficients(0.013184247437242436, 0, -0.013184247437242436, 1.9615533933335245, -0.9741621774545536);
    coeffs[16] = BiquadCoefficients(0.016276405120507823, 0, -0.016276405120507823, 1.9476204990483217, -0.9675565648009634);
    coeffs[17] = BiquadCoefficients(0.02042792937946877, 0, -0.02042792937946877, 1.927774826481906, -0.9592632792381527);
    coeffs[18] = BiquadCoefficients(0.025536567402168895, 0, -0.025536567402168895, 1.8993079685779668, -0.9489528244014288);
    coeffs[19] = BiquadCoefficients(0.03207632908741304, 0, -0.03207632908741304, 1.8579659057171005, -0.9360731478313109);
    coeffs[20] = BiquadCoefficients(0.04002693964888801, 0, -0.04002693964888801, 1.7976451883340874, -0.9201383234713889);
    coeffs[21] = BiquadCoefficients(0.049837373634751374, 0, -0.049837373634751374, 1.7090653995636078, -0.9003663108379056);
    coeffs[22] = BiquadCoefficients(0.06198622495893363, 0, -0.06198622495893363, 1.5790986854909264, -0.8760289407709966);
    coeffs[23] = BiquadCoefficients(0.07691311456052245, 0, -0.07691311456052245, 1.3893296857388144, -0.846184445677453);
    coeffs[24] = BiquadCoefficients(0.09514026526776147, 0, -0.09514026526776147, 1.115827961769152, -0.809744154329511);
    coeffs[25] = BiquadCoefficients(0.11720101054549938, 0, -0.11720101054549938, 0.731756544039447, -0.7656296627775494);
    coeffs[26] = BiquadCoefficients(0.1437144300636289, 0, -0.1437144300636289, 0.21673684317047026, -0.712590728659266);
    coeffs[27] = BiquadCoefficients(0.17533402772397333, 0, -0.17533402772397333, -0.41819234735159183, -0.6493391090491003);
    coeffs[28] = BiquadCoefficients(0.21274992209700935, 0, -0.21274992209700935, -1.0803996522648995, -0.5745067891747677);
    coeffs[29] = BiquadCoefficients(0.2305363666718323, 0, -0.2305363666718323, -1.5386400080912932, -0.5389300106630883);
}

OneThirdOctaveBand::~OneThirdOctaveBand()
{
}

std::vector<double> OneThirdOctaveBand::get_center_frequencies()
{
    return centres;
}

std::vector<std::pair<double,double>> OneThirdOctaveBand::get_lower_upper_pairs()
{
    return lower_upper_pairs;
}

std::vector<BiquadCoefficients> OneThirdOctaveBand::get_coefficients()
{
    return coeffs;
}

void OneThirdOctaveBand::print()
{
    std::cout << "\n\n\nONE THIRD OCTAVE FILTER PRINT\n\n\n";
    for(int i = 0; i<centres.size(); ++i)
    {
        std::cout << i+1 << " & " << centres[i] << " & " << lower_upper_pairs[i].first << " & " << 
            lower_upper_pairs[i].second << " \\\\ \\hline"<< std::endl;
        //std::cout << "Centre frequency: " << centres[i] << " | <" << lower_upper_pairs[i].first << "," << 
        //    lower_upper_pairs[i].second << ">, coeffs{" << coeffs[i].b0 << ", " << coeffs[i].b1 << ", " << 
        //    coeffs[i].b2 << ", " << coeffs[i].a1 << ", " << coeffs[i].a2 << "}" << std::endl;
    }

    std::cout << "\n\n\nFREQUENCY SAMPLING RATE LOWER UPPER\n\n\n";
    double sr = 44100.0;
    for(int i = 0; i<centres.size(); ++i)
    {
        std::cout << i << ": " << lower_upper_pairs[i].first/sr << "," << lower_upper_pairs[i].second/sr << std::endl;
    }
}

