#ifndef DEVICE_MOTORS_HPP
#define DEVICE_MOTORS_HPP

#include "device/motors/TB6612.hpp"
#include "order/Motors.hpp"

namespace device {

class Motors {
public:
    static inline constexpr uint8_t MOTOR_LEFT_DIR1_PIN = 4;
    static inline constexpr uint8_t MOTOR_LEFT_DIR2_PIN = 16;
    static inline constexpr uint8_t MOTOR_LEFT_PWM_PIN = 17;
    static inline constexpr uint8_t MOTOR_RIGHT_DIR1_PIN = 14;
    static inline constexpr uint8_t MOTOR_RIGHT_DIR2_PIN = 33;
    static inline constexpr uint8_t MOTOR_RIGHT_PWM_PIN = 32;

    using MotorLeft =
      device::motors::TB6612<MOTOR_LEFT_DIR1_PIN, MOTOR_LEFT_DIR2_PIN, MOTOR_LEFT_PWM_PIN>;
    using MotorRight =
      device::motors::TB6612<MOTOR_RIGHT_DIR1_PIN, MOTOR_RIGHT_DIR2_PIN, MOTOR_RIGHT_PWM_PIN>;
    using Order = order::Motors;

private:
    MotorLeft left;
    MotorRight right;

public:
    inline Motors() = default;
    inline ~Motors() = default;

    inline auto run(const Order &order) {
        auto result_left = this->left.run(order.left);
        auto result_right = this->right.run(order.right);
        return result_left && result_right;
    }
};

}

#endif // DEVICE_MOTORS_HPP
