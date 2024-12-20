#ifndef DEVICE_TB6612_HPP
#define DEVICE_TB6612_HPP

#include "Arduino.h"

#include "order/motors/TB6612.hpp"

namespace device::motors {

template<uint8_t DIR1_PIN, uint8_t DIR2_PIN, uint8_t PWM_PIN>
class TB6612 {
public:
    TB6612() {
        pinMode(DIR1_PIN, OUTPUT);
        pinMode(DIR2_PIN, OUTPUT);
        pinMode(PWM_PIN, OUTPUT);
        ledcAttach(PWM_PIN, 12800, 16);
    }
    ~TB6612() {
        ledcDetachPin(PWM_PIN);
    }

    inline auto run(const order::motors::TB6612 &order) {
        digitalWrite(DIR1_PIN, order.dir1);
        digitalWrite(DIR2_PIN, order.dir2);
        return ledcWrite(PWM_PIN, order.pwm);
    }
};

}

#endif // DEVICE_TB6612_HPP
