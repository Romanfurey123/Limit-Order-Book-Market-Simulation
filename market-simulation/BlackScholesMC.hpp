#pragma once
#include "Random.hpp"

class BlackScholesMC {
public:
    double S0, r, sigma;
    RNG rng;
    BlackScholesMC(double S0_, double r_, double sigma_, uint64_t seed = 0) : S0(S0_), r(r_), sigma(sigma_), rng(seed) {}
    double european_call_price(double K, double T, int npaths = 100000, int steps = 1);
};
