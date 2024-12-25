#ifndef HELPER_MATH_ANALYSIS_ARITHMETIC_HPP
#define HELPER_MATH_ANALYSIS_ARITHMETIC_HPP

#include <type_traits>

namespace helper::math::analysis {

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

}

#endif // HELPER_MATH_ANALYSIS_ARITHMETIC_HPP
