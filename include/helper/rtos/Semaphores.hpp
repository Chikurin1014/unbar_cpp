#ifndef HELPER_RTOS_SEMAPHORES_HPP
#define HELPER_RTOS_SEMAPHORES_HPP

#include "helper/rtos/semaphores/LockGuard.hpp"
#include "helper/rtos/semaphores/Semaphore.hpp"

namespace helper::rtos {

using Semaphore = semaphores::Semaphore;
using LockGuard = semaphores::LockGuard;

}

#endif // HELPER_RTOS_SEMAPHORES_HPP
