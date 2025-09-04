#include "LOBParser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<LOBMessage> parse_lob_csv(const std::string& filename) {
    std::vector<LOBMessage> out;
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open LOB file: " << filename << "\n";
        return out;
    }
    std::string line;
    // expected CSV header optional we robustly parse lines of form:
    // timestamp,event,side,price,size
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> toks;
        while (std::getline(ss, token, ',')) toks.push_back(token);
        if (toks.size() < 5) continue;
        try {
            double ts = std::stod(toks[0]);
            std::string evt = toks[1];
            char side = toks[2].empty() ? ' ' : toks[2][0];
            double price = std::stod(toks[3]);
            double size = std::stod(toks[4]);
            out.emplace_back(ts, evt, side, price, size);
        }
        catch (...) {
            continue;
        }
    }
    return out;
}
