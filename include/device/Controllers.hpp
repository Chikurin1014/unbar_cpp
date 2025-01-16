#ifndef DEVICE_CONTROLLER_HPP
#define DEVICE_CONTROLLER_HPP

#include "PS4Controller.h"

#include "device/controllers/Display.hpp"

namespace device {

class Controllers {
public:
    inline static constexpr char CONTROLLER_MAC[] = "";

    using RemoteController = PS4Controller;
    using Display = controllers::Display<5, 2, 15>;

    RemoteController rc;
    Display display;

    Controllers()
      : rc{}
      , display{} {
        if (CONTROLLER_MAC != "") {
            this->rc.begin(CONTROLLER_MAC);
        }
    }
};

}

#endif // DEVICE_CONTROLLER_HPP
