#ifndef ORDER_UNBAR_HPP
#define ORDER_UNBAR_HPP

#include "order/motors/TB6612.hpp"

namespace order {

struct Motors {
    using MotorDriver = motors::TB6612;

    MotorDriver left;
    MotorDriver right;

    static inline auto stop() {
        return Motors{MotorDriver::stop(), MotorDriver::stop()};
    };
};

}

#endif // ORDER_UNBAR_HPP
