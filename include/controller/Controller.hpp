#ifndef CONTROLLER_CONTROLLER_HPP
#define CONTROLLER_CONTROLLER_HPP

#include <cmath>

#include "Adafruit_BNO055.h"

#include "controller/LowPassFilter.hpp"
#include "order/Motors.hpp"

namespace controller {

class Controller {
private:
    constexpr static double K_P = 6.0 / std::numbers::pi;
    constexpr static double K_D = 0.0 * K_P;
    constexpr static double T_F = 0.07;

public:
    using Input = imu::Vector<3>;
    using Output = order::Motors;
    struct State {
        double time;
        double target_angle;
        LowPassFilter error;
        double error_diff;
    };

private:
    State state;

public:
    Controller();
    auto step(const Input &input, double time) -> Output;
    auto get_state() const -> const State &;
};

Controller::Controller()
  : state{.time = 0.0, .target_angle = 0.0, .error = LowPassFilter(T_F), .error_diff = 0.0} {}

auto Controller::step(const Input &input, double time) -> Output {
    // update time
    auto dt = time - this->state.time;
    this->state.time = time;

    // update state & calculate output
    auto angle = std::atan2(input.y(), input.z());
    auto previous_error = this->state.error.get_value();
    auto error = this->state.error.step(this->state.target_angle - angle, time);
    this->state.error_diff = (error - previous_error) / dt;

    return Output{
      .left = Output::MotorDriver::normalize(-K_P * error - K_D * this->state.error_diff),
      .right = Output::MotorDriver::normalize(K_P * error + K_D * this->state.error_diff)};
}

auto Controller::get_state() const -> const State & {
    return this->state;
}

}

#endif // CONTROLLER_CONTROLLER_HPP
