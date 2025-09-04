#include "BlackScholesMC.hpp"
#include <cmath>

double BlackScholesMC::european_call_price(double K, double T, int npaths, int steps) {
    double dt = T / std::max(1, steps);
    double sum = 0.0;
    for (int i = 0; i < npaths; ++i) {
        double S = S0;
        for (int j = 0; j < steps; ++j) {
            double z = rng.normal();
            S *= std::exp((r - 0.5 * sigma * sigma) * dt + sigma * std::sqrt(dt) * z);
        }
        double payoff = std::max(S - K, 0.0);
        sum += payoff;
    }
    double mean = sum / npaths;
    return std::exp(-r * T) * mean;
}
