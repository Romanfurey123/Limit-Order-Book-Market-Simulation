#include "OrderBook.hpp"

void OrderBook::update_level(double price, double size, Side side) {
    if (side == Side::Bid) {
        if (size <= 0.0) {
            auto it = bids.find(price);
            if (it != bids.end()) bids.erase(it);
        }
        else {
            bids[price] = size;
        }
    }
    else {
        if (size <= 0.0) {
            auto it = asks.find(price);
            if (it != asks.end()) asks.erase(it);
        }
        else {
            asks[price] = size;
        }
    }
}

void OrderBook::apply_trade(double price, double size, Side side) {
    if (side == Side::Bid) {
        auto it = bids.find(price);
        if (it == bids.end()) return;
        it->second -= size;
        if (it->second <= 1e-12) bids.erase(it);
    }
    else {
        auto it = asks.find(price);
        if (it == asks.end()) return;
        it->second -= size;
        if (it->second <= 1e-12) asks.erase(it);
    }
}


std::optional<Level> OrderBook::best(Side s) const {
    if (s == Side::Bid) {
        if (bids.empty()) return std::nullopt;
        return Level{ bids.begin()->first, bids.begin()->second };
    }
    else {
        if (asks.empty()) return std::nullopt;
        return Level{ asks.begin()->first, asks.begin()->second };
    }
}
