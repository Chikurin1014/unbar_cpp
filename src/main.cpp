#include <cmath>

#include "Arduino.h"

#include "device/Unbar.hpp"
#include "helper/dummy_include.hpp"

void setup() {
    auto unbar = device::Unbar();
    const auto period = 3000;
    const auto omega = 2 * std::numbers::pi_v<double> / period;
    while (true) {
        auto t = millis();
        auto theta = omega * (t % period);
        auto m_order = order::Motors{
          .left = order::Motors::MotorDriver::normalize(std::cos(theta)),
          .right = order::Motors::MotorDriver::normalize(std::sin(theta)),
        };
        unbar.motors.run(m_order);
        delay(1);
    }
}

void loop() {}
