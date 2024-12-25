#ifndef HELPER_RTOS_TASK_PARAMETERS_HPP
#define HELPER_RTOS_TASK_PARAMETERS_HPP

#include <cstdint>

#include "freertos/FreeRTOS.h"

namespace helper::rtos::task {

struct Parameters {
    const char *name;
    uint32_t stack_size;
    UBaseType_t priority;
    BaseType_t core_id;

    Parameters();
};

inline Parameters::Parameters()
  : name{nullptr}
  , stack_size{configMINIMAL_STACK_SIZE}
  , priority{0}
  , core_id{1} {}

}

#endif // HELPER_RTOS_TASK_PARAMETERS_HPP
