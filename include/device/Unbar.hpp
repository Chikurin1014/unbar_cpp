#ifndef DEVICE_UNBAR_HPP
#define DEVICE_UNBAR_HPP

#include "PS4Controller.h"

#include "device/Controllers.hpp"
#include "device/Motors.hpp"
#include "device/Sensors.hpp"

namespace device {

class Unbar {
public:
    Motors motors;
    Sensors sensors;
    Controllers controllers;

    Unbar() = default;
    ~Unbar() = default;
};

}

#endif // DEVICE_UNBAR_HPP
