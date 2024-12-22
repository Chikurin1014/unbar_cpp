#ifndef HELPER_MATH_TOOLS_ANALYZER_HPP
#define HELPER_MATH_TOOLS_ANALYZER_HPP

#include "helper/math/tools/Differentiator.hpp"
#include "helper/math/tools/Integrator.hpp"

namespace helper::math::tools {

template<class T>
concept Analyzer = Differentiator<T> && Integrator<T> && requires(T analyzer) {
    typename T::Value;
    { analyzer.get_value() } -> std::same_as<typename T::Value>;
};

}

#endif // HELPER_MATH_TOOLS_ANALYZER_HPP
