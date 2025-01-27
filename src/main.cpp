#include <cmath>
#include <mutex>

#include "Arduino.h"

#include "device/Unbar.hpp"
#include "helper/dummy_include.hpp"
#include "helper/rtos/Semaphores.hpp"
#include "helper/rtos/Task.hpp"

using Unbar = device::Unbar;
using Order = device::Motors::Order;
using Semaphore = helper::rtos::Semaphore;
using Task = helper::rtos::Task;
using Spawner = helper::rtos::TaskSpawner;

void setup() {
    Serial.begin(115200);
    auto unbar = Unbar();
    auto unbar_mtx = Semaphore();
    auto controll_task = Spawner()
                           .set_function([&unbar, &unbar_mtx]() {
                               TickType_t tick = 0;
                               constexpr auto DELAY_MS = 10;
                               constexpr auto K_P = 6.0 / std::numbers::pi;
                               constexpr auto K_D = 0.0 * K_P;
                               constexpr auto T_P = 0.05;
                               constexpr auto T_D = 0.05;
                               auto pitch_target = 0.0;
                               auto e = 0.0;
                               auto e_diff = 0.0;
                               auto last_e = 0.0;
                               auto last_time = 0.0;
                               while (true) {
                                   tick = xTaskGetTickCount();
                                   {
                                       auto lk = std::lock_guard(unbar_mtx);
                                       const auto time = pdTICKS_TO_MS(tick) / 1000.0;
                                       const auto dt = time - last_time;
                                       // sensing
                                       const auto accel = unbar.sensors.imu.get_accel();
                                       const auto pitch = std::atan2(accel.y(), accel.z());
                                       // filter
                                       e = (1 - dt / T_P) * e + (pitch_target - pitch) * (dt / T_P);
                                       e_diff = (1 - dt / T_D) * e_diff + (e - last_e) * (dt / T_D);
                                       // offset
                                       //    if (e > 0.05) {
                                       //        e += 0.03 * std::numbers::pi;
                                       //    } else if (e < -0.05) {
                                       //        e -= 0.03 * std::numbers::pi;
                                       //    } else {
                                       //        e = 0.0;
                                       //    }
                                       // control
                                       using MD = Order::MotorDriver;
                                       const auto order = Order{
                                         .left = MD::normalize(-K_P * e - K_D * e_diff),
                                         .right = MD::normalize(K_P * e + K_D * e_diff),
                                       };
                                       Serial.printf(">e:%lf\n>e_diff:%lf\n", e, e_diff);
                                       unbar.motors.run(order);
                                       // update state
                                       last_time = time;
                                       last_e = e;
                                   }
                                   xTaskDelayUntil(&tick, pdMS_TO_TICKS(DELAY_MS));
                               }
                           })
                           .set_stack_size(4096)
                           .set_priority(2)
                           .spawn();
    while (controll_task.is_alive()) {
        // Do nothing
    }
}

void loop() {
    Serial.println("All tasks are finished.");
    delay(1000);
}
