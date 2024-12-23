#ifndef HELPER_RTOS_TASK_SPAWNER_HPP
#define HELPER_RTOS_TASK_SPAWNER_HPP

#include "helper/rtos/task/Parameters.hpp"
#include "helper/rtos/task/RawTask.hpp"

namespace helper::rtos::task {

class Spawner {
private:
    Parameters parameters;

public:
    auto set_function(TaskFunction_t function) -> Spawner &;
    auto set_name(const char *name) -> Spawner &;
    auto set_parameters(void *parameters) -> Spawner &;
    auto set_stack_size(size_t stack_size) -> Spawner &;
    auto set_priority(UBaseType_t priority) -> Spawner &;
    auto set_core0() -> Spawner &;
    auto set_core1() -> Spawner &;
    auto spawn() -> RawTask;
};

inline auto Spawner::set_function(TaskFunction_t function) -> Spawner & {
    this->parameters.function = function;
    return *this;
}

inline auto Spawner::set_name(const char *name) -> Spawner & {
    this->parameters.name = name;
    return *this;
}

inline auto Spawner::set_stack_size(size_t stack_size) -> Spawner & {
    this->parameters.stack_size = static_cast<uint32_t>(stack_size);
    return *this;
}

inline auto Spawner::set_parameters(void *parameters) -> Spawner & {
    this->parameters.parameters = parameters;
    return *this;
}

inline auto Spawner::set_priority(UBaseType_t priority) -> Spawner & {
    this->parameters.priority = priority;
    return *this;
}

inline auto Spawner::set_core0() -> Spawner & {
    this->parameters.core_id = 0;
    return *this;
}

inline auto Spawner::set_core1() -> Spawner & {
    this->parameters.core_id = 1;
    return *this;
}

inline auto Spawner::spawn() -> RawTask {
    return RawTask{this->parameters};
}

}

#endif // HELPER_RTOS_TASK_SPAWNER_HPP
