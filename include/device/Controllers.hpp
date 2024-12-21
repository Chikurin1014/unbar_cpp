#ifndef DEVICE_CONTROLLER_HPP
#define DEVICE_CONTROLLER_HPP

#include "PS4Controller.h"

#include "device/controllers/Display.hpp"

namespace device {

class Controllers {
public:
    inline static constexpr char MAC[] = "";

    using RemoteController = PS4Controller;
    using Display = controllers::Display;

    RemoteController rc;
    Display display;

    Controllers()
      : rc{}
      , display{} {
        rc.begin(MAC);
    }
};

}

#endif // DEVICE_CONTROLLER_HPP
