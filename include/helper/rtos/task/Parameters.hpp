#ifndef HELPER_RTOS_TASK_PARAMETERS_HPP
#define HELPER_RTOS_TASK_PARAMETERS_HPP

#include <cstdint>

#include "freertos/FreeRTOS.h"

namespace helper::rtos::task {

struct Parameters {
    TaskFunction_t function;
    const char *name;
    uint32_t stack_size;
    void *parameters;
    UBaseType_t priority;
    BaseType_t core_id;

    Parameters();
};

inline Parameters::Parameters()
  : function{nullptr}
  , name{nullptr}
  , stack_size{configMINIMAL_STACK_SIZE}
  , parameters{nullptr}
  , priority{0}
  , core_id{1} {}

}

#endif // HELPER_RTOS_TASK_PARAMETERS_HPP
