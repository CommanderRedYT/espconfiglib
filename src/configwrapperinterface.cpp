#include "configwrapperinterface.h"

#include "sdkconfig.h"
#define LOG_LOCAL_LEVEL CONFIG_LOG_LOCAL_LEVEL_CONFIG

// system includes
#include <cstring>
#include <cassert>

// esp-idf includes
#include <esp_log.h>
#include <nvs.h>

namespace espconfig {
namespace {
constexpr const char * const TAG = "CONFIG";
} // namespace

ConfigWrapperInterface::ConfigWrapperInterface(AllowReset allowReset, const char *nvsName) :
    m_allowReset{allowReset == AllowReset::DoReset},
    m_nvsName{nvsName}
{
    {
        const auto length = std::strlen(nvsName);
        if (length >= NVS_KEY_NAME_MAX_SIZE)
            ESP_LOGE(TAG, "invalid nvs key %s (too long %zd)", nvsName, length);
        assert(length < NVS_KEY_NAME_MAX_SIZE);
    }
}

} // namespace espconfig
