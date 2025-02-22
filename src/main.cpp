#include <cmath>
#include <functional>
#include <mutex>

#include "Arduino.h"

#include "controller/Controller.hpp"
#include "device/Unbar.hpp"
#include "helper/dummy_include.hpp"
#include "helper/rtos/Semaphores.hpp"
#include "helper/rtos/Task.hpp"
#include "order/Motors.hpp"

auto update_tick(TickType_t &tick) -> void {
    while (true) {
        tick = xTaskGetTickCount();
        vTaskDelayUntil(&tick, pdMS_TO_TICKS(1));
    }
}

auto debug_print(const controller::Controller &controller, helper::rtos::Semaphore &mtx_serial)
  -> void {
    while (true) {
        auto state = controller.get_state();
        {
            auto _lock = std::lock_guard(mtx_serial);
            Serial.printf(">time:%lf\n", state.time);
            Serial.printf(">target_angle:%lf\n", state.target_angle);
            Serial.printf(">error:%lf\n", state.error.get_value());
            Serial.printf(">error_diff:%lf\n", state.error_diff);
        }
        delay(50);
    }
}

auto controll(device::Unbar &unbar,
              helper::rtos::Semaphore &mtx_unbar,
              controller::Controller &controller,
              helper::rtos::Semaphore &mtx_controller,
              TickType_t &tick) -> void {
    while (true) {
        // update time
        auto time = pdTICKS_TO_MS(tick) / 1000.0;
        {
            auto _lock = std::scoped_lock(mtx_unbar, mtx_controller);
            auto input = unbar.sensors.imu.get_accel();
            auto output = controller.step(input, time);
            unbar.motors.run(output);
        }
        vTaskDelayUntil(&tick, pdMS_TO_TICKS(10));
    }
}

void setup() {
    Serial.begin(115200);
    auto mtx_serial = helper::rtos::Semaphore();
    auto unbar = device::Unbar();
    auto mtx_unbar = helper::rtos::Semaphore();
    auto tick = xTaskGetTickCount();
    auto controller = controller::Controller();
    auto mtx_controller = helper::rtos::Semaphore();

    auto update_tick_task = helper::rtos::TaskSpawner()
                              .set_core1()
                              .set_priority(2)
                              .set_function(std::bind(update_tick, std::ref(tick)))
                              .spawn();

    auto controll_task = helper::rtos::TaskSpawner()
                           .set_core1()
                           .set_priority(1)
                           .set_function(std::bind(controll,
                                                   std::ref(unbar),
                                                   std::ref(mtx_unbar),
                                                   std::ref(controller),
                                                   std::ref(mtx_controller),
                                                   std::ref(tick)))
                           .set_stack_size(4096)
                           .spawn();

    auto debug_print_task =
      helper::rtos::TaskSpawner()
        .set_core0()
        .set_priority(0)
        .set_function(std::bind(debug_print, std::ref(controller), std::ref(mtx_serial)))
        .set_stack_size(4096)
        .spawn();

    while (update_tick_task.is_alive()) {
        // do nothing
    }
}

void loop() {}
