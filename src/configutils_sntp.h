#pragma once

// esp-idf includes
#include <esp_sntp.h>

// local includes
#include "configutils_priv_enum.h"

namespace espconfig {

IMPLEMENT_NVS_GET_SET_ENUM(sntp_sync_mode_t)

} // namespace espconfig
