#ifndef DEVICE_CONTROLLER_DISPLAY_HPP
#define DEVICE_CONTROLLER_DISPLAY_HPP

#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"

namespace device::controllers {

template<uint8_t DISPLAY_CS, uint8_t DISPLAY_DC, uint8_t TOUCH_CS>
class Display {
public:
    inline static constexpr uint8_t DISPLAY_CS = DISPLAY_CS;
    inline static constexpr uint8_t DISPLAY_DC = DISPLAY_DC;
    inline static constexpr uint8_t TOUCH_CS = TOUCH_CS;

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
