#include "HestonMC.hpp"
#include <cmath>
#include <algorithm>

// full truncation Euler scheme for variance
double HestonMC::european_call_price(double K, double T, int npaths, int steps) {
    double dt = T / std::max(1, steps);
    double discount = std::exp(-r * T);
    double sum = 0.0;
    for (int i = 0; i < npaths; ++i) {
        double S = S0;
        double v = v0;
        for (int j = 0; j < steps; ++j) {
            // correlated normals: Z1 and Z2, with corr=rho
            double z1 = rng.normal();
            double z2 = rng.normal();
            double w1 = z1;
            double w2 = rho * z1 + std::sqrt(1 - rho * rho) * z2;

            // variance full truncation Euler
            double dv = kappa * (theta - std::max(0.0, v)) * dt + xi * std::sqrt(std::max(0.0, v)) * std::sqrt(dt) * w2;
            v += dv;
            v = std::max(0.0, v);

            // stock log Euler
            S *= std::exp((r - 0.5 * v) * dt + std::sqrt(std::max(0.0, v)) * std::sqrt(dt) * w1);
        }
        double payoff = std::max(S - K, 0.0);
        sum += payoff;
    }
    double mean = sum / npaths;
    return discount * mean;
}
