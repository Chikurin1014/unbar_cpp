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
    imu::Vector<3> last_vec;
    imu::Quaternion last_quat;

    constexpr inline static auto is_valid(double v) {
        return v >= 0.0105 || v <= -0.0105;
    }

public:
    Imu()
      : wire{I2C_BUS}
      , last_vec{0, 0, 0}
      , last_quat{1, 0, 0, 0} {
        pinMode(RESET_PIN, OUTPUT);
        pinMode(I2C_SDA, INPUT_PULLUP);
        pinMode(I2C_SCL, INPUT_PULLUP);
        this->imu = Adafruit_BNO055{ID, ADDR, &this->wire};
        this->restart();
    }
    ~Imu() {
        digitalWrite(RESET_PIN, LOW);
    }

    inline auto get_accel() {
        auto v = this->imu.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
        if (is_valid(v[2])) {
            this->last_vec = v;
        }
        return this->last_vec;
    }

    inline auto get_mag() {
        auto v = this->imu.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
        if (is_valid(v[2])) {
            this->last_vec = v;
        }
        return this->last_vec;
    }

    inline auto get_gyro() {
        auto v = this->imu.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
        if (is_valid(v[2])) {
            this->last_vec = v;
        }
        return this->last_vec;
    }

    inline auto get_euler() {
        auto v = this->imu.getVector(Adafruit_BNO055::VECTOR_EULER);
        if (is_valid(v[2])) {
            this->last_vec = v;
        }
        return this->last_vec;
    }

    inline auto get_lineacc() {
        auto v = this->imu.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
        if (is_valid(v[2])) {
            this->last_vec = v;
        }
        return this->last_vec;
    }

    inline auto get_gravity() {
        auto v = this->imu.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
        if (is_valid(v[2])) {
            this->last_vec = v;
        }
        return this->last_vec;
    }

    inline auto get_quat() {
        auto q = this->imu.getQuat();
        if (is_valid(q.z())) {
            this->last_quat = q;
        }
        return this->last_quat;
    }

    inline auto get_temp() {
        return this->imu.getTemp();
    }

    inline auto restart() {
        digitalWrite(RESET_PIN, LOW);
        delay(1);
        digitalWrite(RESET_PIN, HIGH);
        this->imu.begin();
        this->wire.setPins(I2C_SDA, I2C_SCL);
        this->wire.setClock(50000);
        this->imu.setExtCrystalUse(false);
    }

    inline auto is_calibrated() {
        return this->imu.isFullyCalibrated();
    }
};

}

#endif // DEVICE_SENSORS_IMU_HPP
