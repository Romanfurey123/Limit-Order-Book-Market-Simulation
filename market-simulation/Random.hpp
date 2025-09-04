#pragma once
#include <random>
#include <cstdint>

struct RNG {
    std::mt19937_64 gen;
    explicit RNG(uint64_t seed = std::random_device{}()) : gen(seed) {}
    double normal() {
        thread_local static std::normal_distribution<double> d(0.0, 1.0);
        return d(gen);
    }
    double uniform() {
        thread_local static std::uniform_real_distribution<double> u(0.0, 1.0);
        return u(gen);
    }
    uint64_t next_uint64() { return gen(); }
};
