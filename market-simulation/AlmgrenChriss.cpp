#include "AlmgrenChriss.hpp"
#include <cmath>
#include <vector>

std::vector<double> almgren_chriss_schedule(double X, int N, double T, double sigma, double eta, double gamma, double lambda) {
    std::vector<double> x(N + 1, 0.0);
    if (N <= 0) return x;
    double dt = T / N;
    // continuous approx parameter
    double kappa = 0.0;
    if (eta > 0.0) {
        kappa = std::sqrt((lambda * sigma * sigma) / eta);
    }
    if (kappa == 0.0) {
        // linear schedule fallback
        for (int i = 0; i <= N; ++i) x[i] = X * (1.0 - (double)i / N);
        return x;
    }
    double denom = std::sinh(kappa * T);
    if (denom == 0.0) {
        for (int i = 0; i <= N; ++i) x[i] = X * (1.0 - (double)i / N);
        return x;
    }
    for (int i = 0; i <= N; ++i) {
        double ti = i * dt;
        x[i] = X * std::sinh(kappa * (T - ti)) / denom;
    }
    return x;
}
