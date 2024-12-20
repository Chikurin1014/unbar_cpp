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
    };
};

}

#endif // ORDER_TB6612_HPP
