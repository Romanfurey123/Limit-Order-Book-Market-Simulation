# Limit Order Book Market Simulation

A C++17 market microstructure sandbox. It maintains a price-level limit order
book, replays LOBSTER-style tick messages from a CSV file, and lets an
execution algorithm trade against the book during the replay — printing the
best bid/ask and the algo's fill progress at every tick.

I built this to get a working feel for how execution algorithms interact with
an order book at the tick level, rather than just reading about it.

## What's inside

- **`OrderBook`** — price-level book kept in two sorted maps (bids descending,
  asks ascending). Handles LOBSTER-style level updates (size ≤ 0 deletes the
  level), trades that consume liquidity, and best-bid/best-ask queries.
- **`LOBParser`** — reads `timestamp,event,side,price,size` messages from CSV.
  `synthetic_lob.csv` is a small hand-written feed to replay; swapping in a
  real LOBSTER export is just a matter of formatting.
- **`VWAPAlgo`** — an execution agent (built on a minimal `Agent`/
  `ExecutionAlgo` interface) that works a parent order along a time schedule,
  crossing the spread against the best opposite level whenever it falls
  behind target.
- **`AlmgrenChriss`** — the closed-form Almgren–Chriss optimal liquidation
  schedule (the sinh solution, falling back to a linear schedule when risk
  aversion or temporary impact is zero).
- **`BlackScholesMC` / `HestonMC`** — Monte Carlo pricers for European calls
  under GBM and under Heston (full-truncation Euler for the variance
  process), sharing a small `mt19937_64` RNG wrapper.

## Building and running

Open `market-simulation.sln` in Visual Studio (2019 or later) and run. Or with
g++:

```
cd market-simulation
g++ -std=c++17 -O2 *.cpp -o market_sim
./market_sim
```

Run it from the `market-simulation` folder so it finds `synthetic_lob.csv`.
The demo replays the feed while a VWAP agent buys 200 shares over 5 seconds,
logging the book state and the agent's cumulative fills tick by tick.

## Limitations and where it's going

- The book is price-level, not order-by-order, so there's no queue position —
  fine for studying schedules and spread-crossing, not for queue modelling.
- The "VWAP" schedule is linear in time (effectively TWAP-shaped) because the
  synthetic feed has no volume profile to weight against yet.
- The Almgren–Chriss schedule and the two option pricers compile and work but
  aren't wired into the replay loop yet. The plan is to drive an execution
  agent with the A–C schedule and compare its costs against VWAP on the same
  feed, and to add a simple market-maker agent so the two interact.
