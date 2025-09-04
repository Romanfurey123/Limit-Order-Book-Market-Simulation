#pragma once
#include "Random.hpp"

class HestonMC {
public:
    double S0, v0, r, kappa, theta, xi, rho;
    RNG rng;
    HestonMC(double S0_, double v0_, double r_, double kappa_, double theta_, double xi_, double rho_, uint64_t seed = 0)
        : S0(S0_), v0(v0_), r(r_), kappa(kappa_), theta(theta_), xi(xi_), rho(rho_), rng(seed) {
    }

    double european_call_price(double K, double T, int npaths = 100000, int steps = 100);
};
