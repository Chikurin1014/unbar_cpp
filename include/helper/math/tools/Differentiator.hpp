#ifndef HELPER_MATH_TOOLS_DIFFERENTIATOR_HPP
#define HELPER_MATH_TOOLS_DIFFERENTIATOR_HPP

#include <concepts>

#include "helper/math/tools/Arithmetic.hpp"

namespace helper::math::tools {

template<class T>
concept Differentiator = requires(T diff) {
    typename T::Value;
    typename T::Time;
    requires Arithmetic<typename T::Value>;
    { std::declval<typename T::Value>() / std::declval<typename T::Time>() } -> std::same_as<typename T::Value>;
    { diff.set(std::declval<typename T::Value>(), std::declval<typename T::Time>()) } -> std::same_as<void>;
    { diff.get_differential() } -> std::same_as<typename T::Value>;
};

}

#endif // HELPER_MATH_TOOLS_DIFFERENTIATOR_HPP
