#pragma once
#include "Agent.hpp"

class ExecutionAlgo : public Agent {
public:
    double remaining_qty;
    double initial_qty;
    bool is_buy;
    ExecutionAlgo(double qty, bool buy = true) : remaining_qty(qty), initial_qty(qty), is_buy(buy) {}
    virtual ~ExecutionAlgo() = default;
};
