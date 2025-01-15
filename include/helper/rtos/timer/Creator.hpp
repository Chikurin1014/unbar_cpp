#ifndef HELPER_RTOS_TIMER_CREATOR_HPP
#define HELPER_RTOS_TIMER_CREATOR_HPP

#include "freertos/FreeRTOS.h"

#include "helper/rtos/timer/Parameters.hpp"
#include "helper/rtos/timer/RawTimer.hpp"

namespace helper::rtos::timer {

class Creator {
public:
    using Timer = timer::RawTimer;
    using Parameters = timer::Parameters;
    using Mode = timer::Mode;

private:
    Parameters parameters;
    TimerCallbackFunction_t function;

public:
    Creator() = default;
    ~Creator() = default;

    auto set_name(const char *name) -> Creator &;
    auto set_period_ms(uint32_t period_ms) -> Creator &;
    auto set_mode(Mode mode) -> Creator &;
    template<typename T>
    auto set_id(T id) -> Creator &;
    auto set_callback(TimerCallbackFunction_t function) -> Creator &;
    auto create() -> Timer;
};

inline auto Creator::set_name(const char *name) -> Creator & {
    this->parameters.name = name;
    return *this;
}

inline auto Creator::set_period_ms(uint32_t period_ms) -> Creator & {
    this->parameters.period = pdMS_TO_TICKS(period_ms);
    return *this;
}

inline auto Creator::set_mode(Mode mode) -> Creator & {
    this->parameters.auto_reload = static_cast<BaseType_t>(mode);
    return *this;
}

template<typename T>
inline auto Creator::set_id(T id) -> Creator & {
    this->parameters.id = reinterpret_cast<void *>(id);
    return *this;
}

inline auto Creator::set_callback(TimerCallbackFunction_t function) -> Creator & {
    this->function = function;
    return *this;
}

inline auto Creator::create() -> Timer {
    return Timer{this->parameters, this->function};
}

}

#endif // HELPER_RTOS_TIMER_CREATOR_HPP
