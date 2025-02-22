#ifndef CONTROLLER_LOWPASSFILTER_HPP
#define CONTROLLER_LOWPASSFILTER_HPP

namespace controller {

class LowPassFilter {
private:
    double time_constant;
    double value;
    double time;

public:
    LowPassFilter(double time_constant);
    auto step(double input, double time) -> double;
    auto get_value() const -> double;
    auto get_time() const -> double;
    auto get_time_constant() const -> double;
    auto set_time(double time) -> void;
    auto set_time_constant(double time_constant) -> void;
};

LowPassFilter::LowPassFilter(double time_constant)
  : time_constant(time_constant)
  , value(0.0)
  , time(0.0) {}

auto LowPassFilter::step(double input, double time) -> double {
    auto dt = time - this->time;
    this->time = time;

    this->value = (1 - dt / this->time_constant) * this->value + dt / this->time_constant * input;
    return this->value;
}
auto LowPassFilter::get_value() const -> double {
    return this->value;
}

auto LowPassFilter::get_time() const -> double {
    return this->time;
}

auto LowPassFilter::get_time_constant() const -> double {
    return this->time_constant;
}

auto LowPassFilter::set_time(double time) -> void {
    this->time = time;
}

auto LowPassFilter::set_time_constant(double time_constant) -> void {
    this->time_constant = time_constant;
}

}

#endif // CONTROLLER_LOWPASSFILTER_HPP
