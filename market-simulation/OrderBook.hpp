#pragma once
#include <map>
#include <optional>

enum class Side { Bid, Ask };

struct Level {
    double price;
    double quantity;
};

class OrderBook {
public:
    // descending bids, ascending asks
    std::map<double, double, std::greater<>> bids;
    std::map<double, double> asks;

    OrderBook() = default;

    // apply LOBSTER style update: set size at price (if size<=0 remove)
    void update_level(double price, double size, Side side);

    // apply a trade consuming liquidity at price
    void apply_trade(double price, double size, Side side);

    std::optional<Level> best(Side s) const;
};
