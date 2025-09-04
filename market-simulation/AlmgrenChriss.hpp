#pragma once
#include <vector>

// compute discrete Almgren Chriss schedule (x[0]=initial, x[N]=~0)
// X initial shares, N steps, T total time, sigma volatility, eta temporary, gamma permanent, lambda risk aversion
std::vector<double> almgren_chriss_schedule(double X, int N, double T, double sigma, double eta, double gamma, double lambda);
