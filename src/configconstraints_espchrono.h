#pragma once

// system includes
#include <string>

// 3rdparty lib includes
#include <tl/expected.hpp>
#include <fmt/core.h>

// local includes
#include "configwrapper.h"
#include "espchrono.h"

namespace espconfig {
inline ConfigConstraintReturnType MinTimeSyncInterval(espchrono::milliseconds32 val)
{
    using namespace std::chrono_literals;
    if (val < 15s)
        return tl::make_unexpected("SNTPv4 RFC 4330 enforces a minimum update time of 15 seconds");
    return {};
}
} // namespace espconfig
