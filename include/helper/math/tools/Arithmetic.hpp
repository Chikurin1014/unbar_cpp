#ifndef HELPER_MATH_TOOLS_ARITHMETIC_HPP
#define HELPER_MATH_TOOLS_ARITHMETIC_HPP

#include <type_traits>

namespace helper::math::tools {

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

}

#endif // HELPER_MATH_TOOLS_ARITHMETIC_HPP
