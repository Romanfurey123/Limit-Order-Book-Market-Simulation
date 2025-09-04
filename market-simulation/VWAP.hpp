#pragma once
#include "ExecutionAlgo.hpp"

class VWAPAlgo : public ExecutionAlgo {
private:
    double start_time, end_time;
    double traded;
public:
    VWAPAlgo(double qty, double t0, double t1, bool buy = true)
        : ExecutionAlgo(qty, buy), start_time(t0), end_time(t1), traded(0.0) {
    }
    void on_tick(const MarketContext& ctx) override;
    double get_traded() const { return traded; }
};
