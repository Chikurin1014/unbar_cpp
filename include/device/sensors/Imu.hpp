#ifndef DEVICE_SENSORS_IMU_HPP
#define DEVICE_SENSORS_IMU_HPP

#ifndef __I2C_BUS
#define __I2C_BUS 0
#endif

#ifndef __I2C_SDA
#define __I2C_SDA 21
#endif

#ifndef __I2C_SCL
#define __I2C_SCL 22
#endif

#include "Adafruit_BNO055.h"
#include "Wire.h"

namespace device::sensors {

template<uint8_t ADDR, uint8_t RESET_PIN, int16_t ID = -1>
class Imu {
private:
    inline static constexpr uint8_t ADDR = ADDR;
    inline static constexpr uint8_t RESET_PIN = RESET_PIN;
    inline static constexpr int16_t ID = ID;
    inline static constexpr uint8_t I2C_BUS = __I2C_BUS;
    inline static constexpr uint8_t I2C_SDA = __I2C_SDA;
    inline static constexpr uint8_t I2C_SCL = __I2C_SCL;

    Adafruit_BNO055 imu;
    TwoWire wire;

public:
    Imu()
      : wire{I2C_BUS} {
        pinMode(RESET_PIN, OUTPUT);
        this->wire.setPins(I2C_SDA, I2C_SCL);
        this->imu = Adafruit_BNO055{ID, ADDR, &this->wire};
        this->restart();
    }
    ~Imu() {
        digitalWrite(RESET_PIN, LOW);
    }

    inline auto get_accel() {
        return this->imu.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    }
    inline auto get_quat() {
        return this->imu.getQuat();
    }

    inline auto restart() {
        digitalWrite(RESET_PIN, LOW);
        delay(1);
        digitalWrite(RESET_PIN, HIGH);
        this->imu.begin();
    }

    inline auto is_calibrated() {
        return this->imu.isFullyCalibrated();
    }
};
}

#endif // DEVICE_SENSORS_IMU_HPP
