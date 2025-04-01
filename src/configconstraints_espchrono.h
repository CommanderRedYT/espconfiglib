#pragma once

// system includes
#include <expected>

// local includes
#include "configwrapper.h"
#include "espchrono.h"

namespace espconfig {
inline ConfigConstraintReturnType MinTimeSyncInterval(espchrono::milliseconds32 val)
{
    using namespace std::chrono_literals;
    if (val < 15s)
        return std::unexpected("SNTPv4 RFC 4330 enforces a minimum update time of 15 seconds");
    return {};
}
} // namespace espconfig
