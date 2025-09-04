#include <iostream>
#include "OrderBook.hpp"
#include "LOBParser.hpp"
#include "VWAP.hpp"

int main() {
    std::cout << "Synthetic LOBSTER replay demo\n";

    // load synthetic CSV
    auto msgs = parse_lob_csv("synthetic_lob.csv");

    OrderBook ob;
    VWAPAlgo vwap(200.0, 0.0, 5.0, true); // buy 200 shares over 5 seconds
    MarketContext ctx{ &ob, 0.0 };

    for (auto& m : msgs) {
        double ts; std::string evt; char side; double price, size;
        std::tie(ts, evt, side, price, size) = m;
        ctx.time = ts;

        if (evt == "update") {
            ob.update_level(price, size, (side == 'B') ? Side::Bid : Side::Ask);
        }
        else if (evt == "trade") {
            ob.apply_trade(price, size, (side == 'B') ? Side::Bid : Side::Ask);
        }

        // let VWAP agent react each tick
        vwap.on_tick(ctx);

        auto bestBid = ob.best(Side::Bid);
        auto bestAsk = ob.best(Side::Ask);

        std::cout << "t=" << ts
            << " bestBid=" << (bestBid ? std::to_string(bestBid->price) : "nil")
            << " bestAsk=" << (bestAsk ? std::to_string(bestAsk->price) : "nil")
            << " VWAP_traded=" << vwap.get_traded()
            << "\n";
    }

    return 0;
}
