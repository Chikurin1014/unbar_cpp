#ifndef DEVICE_SENSORS_HPP
#define DEVICE_SENSORS_HPP

#include "device/sensors/Imu.hpp"

namespace device {

class Sensors {
public:
    using Imu = sensors::Imu<0x28, 27>;

    Imu imu;

    Sensors() = default;
    ~Sensors() = default;
};

}

#endif // DEVICE_SENSORS_HPP
