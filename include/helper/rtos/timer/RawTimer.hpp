#ifndef HELPER_RTOS_TIMER_RAWTIMER_HPP
#define HELPER_RTOS_TIMER_RAWTIMER_HPP

#include <functional>

#include "freertos/FreeRTOS.h"

#include "helper/rtos/timer/Mode.hpp"
#include "helper/rtos/timer/Parameters.hpp"

namespace helper::rtos::timer {

class RawTimer {
public:
    using Parameters = timer::Parameters;
    using Mode = timer::Mode;

private:
    TimerHandle_t handle;
    TimerCallbackFunction_t function;

public:
    RawTimer(Parameters parameters, TimerCallbackFunction_t function);
    ~RawTimer();

    auto get_handle() const -> const TimerHandle_t;
    auto start(uint32_t wait_ms = 0) -> bool;
    auto stop(uint32_t wait_ms = 0) -> bool;
    auto reset(uint32_t wait_ms = 0) -> bool;
    template<typename T>
    auto get_id() const -> T;
    auto is_active() const -> bool;
    auto get_period_ms() const -> uint32_t;
    auto get_expiry_ms() const -> uint32_t;
    auto get_mode() const -> Mode;
    auto set_period_ms(uint32_t period_ms) -> void;
    auto set_mode(Mode mode) -> void;
};

inline RawTimer::RawTimer(Parameters parameters, TimerCallbackFunction_t function)
  : handle{}
  , function{function} {
    this->handle = xTimerCreate(
      parameters.name, parameters.period, parameters.auto_reload, parameters.id, this->function);
}

inline RawTimer::~RawTimer() {
    xTimerDelete(this->handle, 0);
}

inline auto RawTimer::get_handle() const -> const TimerHandle_t {
    return this->handle;
}

inline auto RawTimer::start(uint32_t wait_ms) -> bool {
    return static_cast<bool>(xTimerStart(this->handle, pdMS_TO_TICKS(wait_ms)));
}

inline auto RawTimer::stop(uint32_t wait_ms) -> bool {
    return static_cast<bool>(xTimerStop(this->handle, pdMS_TO_TICKS(wait_ms)));
}

inline auto RawTimer::reset(uint32_t wait_ms) -> bool {
    return static_cast<bool>(xTimerReset(this->handle, pdMS_TO_TICKS(wait_ms)));
}

template<typename T>
inline auto RawTimer::get_id() const -> T {
    return reinterpret_cast<T>(pvTimerGetTimerID(this->handle));
}

inline auto RawTimer::is_active() const -> bool {
    return static_cast<bool>(xTimerIsTimerActive(this->handle));
}

inline auto RawTimer::get_period_ms() const -> uint32_t {
    return pdTICKS_TO_MS(xTimerGetPeriod(this->handle));
}

inline auto RawTimer::get_expiry_ms() const -> uint32_t {
    return pdTICKS_TO_MS(xTimerGetExpiryTime(this->handle));
}

inline auto RawTimer::get_mode() const -> Mode {
    return static_cast<Mode>(xTimerIsTimerActive(this->handle));
}

inline auto RawTimer::set_period_ms(uint32_t period_ms) -> void {
    xTimerChangePeriod(this->handle, pdMS_TO_TICKS(period_ms), 0);
}

inline auto RawTimer::set_mode(Mode mode) -> void {
    vTimerSetReloadMode(this->handle, static_cast<BaseType_t>(mode));
}

}
#endif // HELPER_RTOS_TIMER_RAWTIMER_HPP
