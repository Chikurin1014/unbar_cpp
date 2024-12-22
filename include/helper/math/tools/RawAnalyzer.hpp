#ifndef HELPER_MATH_TOOLS_RAWANALYZER_HPP
#define HELPER_MATH_TOOLS_RAWANALYZER_HPP

#include <cstddef>

#include "helper/math/tools/Analyzer.hpp"

namespace helper::math::tools {

class RawAnalyzer {
public:
    using Value = double;
    using Time = size_t;

private:
    Value prev_value;
    Time prev_time;
    Value diff;
    Value integral;

public:
    RawAnalyzer(Value first_value = 0.0, Time first_time = 0);
    ~RawAnalyzer() = default;

    auto set(Value value, Time time) -> void;
    auto get_value() const -> Value;
    auto get_differential() const -> Value;
    auto get_integral() const -> Value;
};

inline RawAnalyzer::RawAnalyzer(Value first_value, Time first_time)
  : prev_value{first_value}
  , prev_time{first_time}
  , diff{0.0}
  , integral{0.0} {}

inline auto RawAnalyzer::set(Value value, Time time) -> void {
    const auto dt = time - this->prev_time;
    const auto dv = value - this->prev_value;
    this->diff = dv / dt;
    this->integral += value * dt;
    this->prev_value = value;
    this->prev_time = time;
}

inline auto RawAnalyzer::get_value() const -> Value {
    return this->prev_value;
}

inline auto RawAnalyzer::get_differential() const -> Value {
    return this->diff;
}

inline auto RawAnalyzer::get_integral() const -> Value {
    return this->integral;
}

}

static_assert(helper::math::tools::Analyzer<helper::math::tools::RawAnalyzer>);

#endif // HELPER_MATH_TOOLS_RAWANALYZER_HPP
