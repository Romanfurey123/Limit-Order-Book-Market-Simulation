#include "VWAP.hpp"
#include <algorithm>

void VWAPAlgo::on_tick(const MarketContext& ctx) {
    if (remaining_qty <= 0.0) return;
    if (ctx.time < start_time) return;
    double t = std::min(ctx.time, end_time);
    double elapsed = t - start_time;
    double total = end_time - start_time;
    if (total <= 0.0) return;
    double desired_done = (elapsed / total) * initial_qty;
    double to_do = desired_done - traded;
    if (to_do <= 1e-12) return;

    // simple aggressor to take from best opposite side
    auto side = is_buy ? Side::Ask : Side::Bid;
    auto best = ctx.ob->best(side);
    if (!best) return;
    double qty = std::min(to_do, best->quantity);
    ctx.ob->apply_trade(best->price, qty, side);
    traded += qty;
    remaining_qty -= qty;
}
