#ifndef DEVICE_SENSORS_IMU_HPP
#define DEVICE_SENSORS_IMU_HPP

#include "Adafruit_BNO055.h"

namespace device::sensors {

template<int32_t ID, uint8_t ADDR>
class Imu {
private:
    Adafruit_BNO055 imu;

public:
    Imu()
      : imu{ID, ADDR} {
        this->imu.begin();
    }
    ~Imu() = default;

    inline auto get_accel() {
        return this->imu.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    }
    inline auto get_posture() {
        return this->imu.getVector(Adafruit_BNO055::VECTOR_EULER);
    }
};

}

#endif // DEVICE_SENSORS_IMU_HPP
