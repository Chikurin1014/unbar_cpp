#ifndef DEVICE_SENSORS_IMU_HPP
#define DEVICE_SENSORS_IMU_HPP

#include "Adafruit_BNO055.h"
#include "Wire.h"

namespace device::sensors {

template<uint8_t ADDR, uint8_t RESET_PIN, int16_t ID = -1>
class Imu {
private:
#ifdef UNBAR_I2C_BUS
    constexpr inline static uint8_t I2C_BUS = UNBAR_I2C_BUS;
#else
    constexpr inline static uint8_t I2C_BUS = 0;
#endif
#ifdef UNBAR_I2C_SDA
    constexpr inline static uint8_t I2C_SDA = UNBAR_I2C_SDA;
#else
    constexpr inline static uint8_t I2C_SDA = 21;
#endif
#ifdef UNBAR_I2C_SCL
    constexpr inline static uint8_t I2C_SCL = UNBAR_I2C_SCL;
#else
    constexpr inline static uint8_t I2C_SCL = 22;
#endif

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
