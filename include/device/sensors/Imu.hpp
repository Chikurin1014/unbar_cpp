#ifndef DEVICE_SENSORS_IMU_HPP
#define DEVICE_SENSORS_IMU_HPP

#include "Adafruit_BNO055.h"
#include "Wire.h"

namespace device::sensors {

template<int32_t ID, uint8_t ADDR>
class Imu {
private:
    inline static constexpr uint8_t I2C_SDA = 21;
    inline static constexpr uint8_t I2C_SCL = 22;

    Adafruit_BNO055 imu;
    TwoWire wire;

public:
    Imu()
      : wire{I2C_SDA, I2C_SCL} {
        this->imu = Adafruit_BNO055{ID, ADDR, &this->wire};
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
