#ifndef HELPER_MATH_ANALYSIS_RAWANALYZER_HPP
#define HELPER_MATH_ANALYSIS_RAWANALYZER_HPP

#include <cstddef>

#include "helper/math/analysis/Analyzer.hpp"

namespace helper::math::analysis {

class RawAnalyzer {
public:
    using Value = double;
    using Time = double;

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

/**
 * @brief Construct a new Raw Analyzer object
 *
 * @param first_value (double)
 * @param first_time [s] (double)
 */
inline RawAnalyzer::RawAnalyzer(Value first_value, Time first_time)
  : prev_value{first_value}
  , prev_time{first_time}
  , diff{0.0}
  , integral{0.0} {}

/**
 * @brief Set the value and time for the analyzer.
 *
 * @param value (double)
 * @param time [s] (double)
 */
inline auto RawAnalyzer::set(Value value, Time time) -> void {
    const auto dt = time - this->prev_time;
    const auto dv = value - this->prev_value;
    this->diff = dv / dt;
    this->integral += (value + this->prev_value) * dt / 2.0;
    this->prev_value = value;
    this->prev_time = time;
}

/**
 * @brief Get last value.
 *
 * @return double
 */
inline auto RawAnalyzer::get_value() const -> Value {
    return this->prev_value;
}

/**
 * @brief Get last differential.
 *
 * @return double
 */
inline auto RawAnalyzer::get_differential() const -> Value {
    return this->diff;
}

/**
 * @brief Get integral.
 *
 * @return double
 */
inline auto RawAnalyzer::get_integral() const -> Value {
    return this->integral;
}

}

static_assert(helper::math::analysis::Analyzer<helper::math::analysis::RawAnalyzer>);

#endif // HELPER_MATH_ANALYSIS_RAWANALYZER_HPP
