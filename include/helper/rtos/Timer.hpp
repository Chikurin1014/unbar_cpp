#ifndef HELPER_RTOS_TIMER_HPP
#define HELPER_RTOS_TIMER_HPP

#include "helper/rtos/timer/Creator.hpp"
#include "helper/rtos/timer/Mode.hpp"
#include "helper/rtos/timer/RawTimer.hpp"

namespace helper::rtos {

using Timer = timer::RawTimer;
using TimerCreator = timer::Creator;
using TimerMode = timer::Mode;

}

#endif // HELPER_RTOS_TIMER_HPP
