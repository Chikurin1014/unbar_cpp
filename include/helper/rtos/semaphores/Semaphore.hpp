#ifndef HELPER_RTOS_SEMAPHORES_SEMAPHORE_HPP
#define HELPER_RTOS_SEMAPHORES_SEMAPHORE_HPP

#include "freertos/FreeRTOS.h"

#include "helper/rtos/semaphores/SemaphoreType.hpp"

namespace helper::rtos::semaphores {

class Semaphore {
public:
    using Type = SemaphoreType;

private:
    SemaphoreHandle_t handle;

public:
    Semaphore(Type type);
    ~Semaphore();

    auto try_lock(uint32_t wait_ms = 0) -> bool;
    auto unlock() -> bool;
};

inline Semaphore::Semaphore(Type type) {
    switch (type) {
        case Type::Binary: {
            this->handle = xSemaphoreCreateBinary();
            break;
        }
        case Type::Mutex: {
            this->handle = xSemaphoreCreateMutex();
            break;
        }
    }
}

inline Semaphore::~Semaphore() {
    vSemaphoreDelete(handle);
}

inline auto Semaphore::try_lock(uint32_t wait_ms) -> bool {
    return static_cast<bool>(xSemaphoreTake(handle, pdMS_TO_TICKS(wait_ms)));
}

inline auto Semaphore::unlock() -> bool {
    return static_cast<bool>(xSemaphoreGive(handle));
}

}

#endif // HELPER_RTOS_SEMAPHORES_SEMAPHORE_HPP
