#pragma once
#include <string>
#include <vector>
#include <tuple>

// tiny LOB message: (timestamp_seconds, eventType, side, price, size)
// eventType: "update" or "trade"; side: "B" or "S"
using LOBMessage = std::tuple<double, std::string, char, double, double>;
std::vector<LOBMessage> parse_lob_csv(const std::string& filename);
