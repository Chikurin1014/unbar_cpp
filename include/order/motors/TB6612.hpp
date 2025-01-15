#ifndef ORDER_TB6612_HPP
#define ORDER_TB6612_HPP

#include <cmath>
#include <cstdint>

namespace order::motors {

struct TB6612 {
    bool dir1;
    bool dir2;
    uint16_t pwm;

    static inline auto stop() {
        return TB6612{false, false, 0};
    }

    static inline auto normalize(float value, uint8_t resolution_bits = 10) {
        return TB6612{
          value >= 0,
          value <= 0,
          static_cast<uint16_t>(std::abs(value) * ((1 << resolution_bits) - 1)),
        };
    }
};

}

#endif // ORDER_TB6612_HPP
