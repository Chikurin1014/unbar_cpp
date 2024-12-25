#ifndef HELPER_MATH_ANALYSIS_ANALYZER_HPP
#define HELPER_MATH_ANALYSIS_ANALYZER_HPP

#include "helper/math/analysis/Differentiator.hpp"
#include "helper/math/analysis/Integrator.hpp"

namespace helper::math::analysis {

template<class T>
concept Analyzer = Differentiator<T> && Integrator<T> && requires(T analyzer) {
    typename T::Value;
    { analyzer.get_value() } -> std::same_as<typename T::Value>;
};

}

#endif // HELPER_MATH_ANALYSIS_ANALYZER_HPP
