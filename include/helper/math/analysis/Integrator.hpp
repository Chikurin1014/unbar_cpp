#ifndef HELPER_MATH_ANALYSIS_INTEGRATOR_HPP
#define HELPER_MATH_ANALYSIS_INTEGRATOR_HPP

#include <concepts>

#include "helper/math/analysis/Arithmetic.hpp"

namespace helper::math::analysis {

template<class T>
concept Integrator = requires(T integ) {
    typename T::Value;
    typename T::Time;
    requires Arithmetic<typename T::Value>;
    { std::declval<typename T::Value>() * std::declval<typename T::Time>() } -> std::same_as<typename T::Value>;
    { integ.set(std::declval<typename T::Value>(), std::declval<typename T::Time>()) } -> std::same_as<void>;
    { integ.get_integral() } -> std::same_as<typename T::Value>;
};

}

#endif // HELPER_MATH_ANALYSIS_INTEGRATOR_HPP
