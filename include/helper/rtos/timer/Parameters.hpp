#ifndef HELPER_RTOS_TIMER_PARAMETERS_HPP
#define HELPER_RTOS_TIMER_PARAMETERS_HPP

#include "freertos/FreeRTOS.h"

namespace helper::rtos::timer {

struct Parameters {
    const char *name;
    TickType_t period;
    BaseType_t auto_reload;
    void *id;

    Parameters();
};

inline Parameters::Parameters()
  : name{""}
  , period{pdMS_TO_TICKS(1)}
  , auto_reload{pdTRUE}
  , id{nullptr} {}

}

#endif // HELPER_RTOS_TIMER_PARAMETERS_HPP
