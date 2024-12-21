#ifndef HELPER_RTOS_SEMAPHORES_LOCKGUARD_HPP
#define HELPER_RTOS_SEMAPHORES_LOCKGUARD_HPP

#include "helper/rtos/semaphores/Semaphore.hpp"

namespace helper::rtos::semaphores {

class LockGuard {
private:
    Semaphore &semaphore;
    bool locked;

public:
    LockGuard(Semaphore &semaphore, uint32_t wait_ms = 0);
    ~LockGuard();
    auto operator=(const LockGuard &) -> LockGuard & = delete;

    auto is_locked() const -> bool;
    auto try_lock(uint32_t wait_ms = 0) -> bool;
};

inline LockGuard::LockGuard(Semaphore &semaphore, uint32_t wait_ms)
  : semaphore{semaphore}
  , locked{false} {
    if (this->semaphore.try_lock(wait_ms)) {
        this->locked = true;
    }
}

inline LockGuard::~LockGuard() {
    if (this->is_locked()) {
        this->semaphore.unlock();
    }
}

inline auto LockGuard::is_locked() const -> bool {
    return this->locked;
}

inline auto LockGuard::try_lock(uint32_t wait_ms) -> bool {
    if (this->is_locked()) {
        return true;
    }
    this->locked = this->semaphore.try_lock(wait_ms);
    return locked;
}

}

#endif // HELPER_RTOS_SEMAPHORES_LOCKGUARD_HPP
