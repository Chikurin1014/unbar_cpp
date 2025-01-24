#ifndef HELPER_RTOS_TASK_RAWTASK_HPP
#define HELPER_RTOS_TASK_RAWTASK_HPP

#include <array>
#include <functional>

#include "freertos/FreeRTOS.h"

#include "helper/rtos/task/Parameters.hpp"

namespace helper::rtos::task {

class RawTask {
public:
    using Parameters = task::Parameters;

private:
    TaskHandle_t handle;
    std::function<void()> function;

public:
    RawTask(Parameters parameters, std::function<void()> function);
    ~RawTask();

    auto get_handle() const -> const TaskHandle_t;
    auto suspend();
    auto resume();
    auto abort_delay();
    auto abort();
    auto get_state() -> eTaskState;
    auto is_alive() -> bool;
    auto get_info() -> TaskStatus_t;
    auto get_highwatermark() -> UBaseType_t;

    static auto suspend_thisthread();
    static auto abort_thisthread();
    static auto get_highwatermark_thisthread() -> UBaseType_t;
};

inline RawTask::RawTask(Parameters parameters, std::function<void()> function)
  : handle{}
  , function{function} {
    auto f = [](void *arg) {
        auto f = *reinterpret_cast<std::function<void()> *>(arg);
        f();
        vTaskDelete(nullptr);
    };
    xTaskCreatePinnedToCore(f,
                            parameters.name,
                            parameters.stack_size,
                            &this->function,
                            parameters.priority,
                            &this->handle,
                            parameters.core_id);
}

inline RawTask::~RawTask() {
    if (!this->is_alive()) {
        return;
    }
    vTaskDelete(this->handle);
}

inline auto RawTask::get_handle() const -> const TaskHandle_t {
    return this->handle;
}

inline auto RawTask::suspend() {
    vTaskSuspend(this->handle);
}

inline auto RawTask::resume() {
    vTaskResume(this->handle);
}

inline auto RawTask::abort_delay() {
    xTaskAbortDelay(this->handle);
}

inline auto RawTask::abort() {
    vTaskDelete(this->handle);
}

inline auto RawTask::get_state() -> eTaskState {
    return eTaskGetState(this->handle);
}

inline auto RawTask::is_alive() -> bool {
    return this->get_state() != eTaskState::eDeleted;
}

inline auto RawTask::get_highwatermark() -> UBaseType_t {
    return uxTaskGetStackHighWaterMark(this->handle);
}

inline auto RawTask::get_info() -> TaskStatus_t {
    TaskStatus_t status;
    vTaskGetInfo(this->handle, &status, pdTRUE, eInvalid);
    return status;
}

inline auto RawTask::suspend_thisthread() {
    vTaskSuspend(nullptr);
}

inline auto RawTask::abort_thisthread() {
    vTaskDelete(nullptr);
}

inline auto RawTask::get_highwatermark_thisthread() -> UBaseType_t {
    return uxTaskGetStackHighWaterMark(nullptr);
}

}

#endif // HELPER_RTOS_TASK_RAWTASK_HPP
