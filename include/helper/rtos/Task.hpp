#ifndef HELPER_RTOS_TASK_HPP
#define HELPER_RTOS_TASK_HPP

#include "helper/rtos/task/RawTask.hpp"
#include "helper/rtos/task/Spawner.hpp"

namespace helper::rtos {

using Task = task::RawTask;
using TaskSpawner = task::Spawner;

}

#endif // HELPER_RTOS_TASK_HPP
