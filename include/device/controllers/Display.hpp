#ifndef DEVICE_CONTROLLER_DISPLAY_HPP
#define DEVICE_CONTROLLER_DISPLAY_HPP

#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"

namespace device::controllers {

class Display {
public:
    inline static constexpr uint8_t DISPLAY_CS = 5;
    inline static constexpr uint8_t DISPLAY_DC = 2;
    inline static constexpr uint8_t TOUCH_CS = 15;

    using TFT = Adafruit_ILI9341;
    using Ts = XPT2046_Touchscreen;

    TFT tft;
    Ts ts;

    Display()
      : tft(DISPLAY_CS, DISPLAY_DC)
      , ts(TOUCH_CS) {
        tft.begin();
        ts.begin();
    }
    ~Display() = default;
};

}

#endif // DEVICE_CONTROLLER_DISPLAY_HPP
