#pragma once
#include "OrderBook.hpp"

struct MarketContext {
    OrderBook* ob;
    double time; // seconds since start
};

class Agent {
public:
    virtual ~Agent() = default;
    // called each tick
    virtual void on_tick(const MarketContext& ctx) = 0;
};
