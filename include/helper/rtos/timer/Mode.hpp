#ifndef HELPER_RTOS_TIMER_MODE_HPP
#define HELPER_RTOS_TIMER_MODE_HPP

#include "freertos/FreeRTOS.h"

namespace helper::rtos::timer {

enum class Mode : BaseType_t { Oneshot = pdFALSE, Periodic = pdTRUE };

}

#endif // HELPER_RTOS_TIMER_MODE_HPP
