#pragma once

// local includes
#include "configutils_priv_enum.h"
#include "espchrono.h"

namespace espconfig {

IMPLEMENT_NVS_GET_SET_ENUM(espchrono::DayLightSavingMode)

#define IMPLEMENT_NVS_GET_SET_CHRONO(Name) \
    inline esp_err_t nvs_get(nvs_handle handle, const char* key, Name* out_value) \
    { \
        Name::rep temp; \
        const auto result = nvs_get(handle, key, &temp); \
        if (result == ESP_OK && out_value) \
            *out_value = Name{temp}; \
        return result; \
    } \
    \
    inline esp_err_t nvs_set(nvs_handle handle, const char* key, Name value) \
    { \
        return nvs_set(handle, key, Name::rep(value.count())); \
    }

IMPLEMENT_NVS_GET_SET_CHRONO(espchrono::milliseconds32)
IMPLEMENT_NVS_GET_SET_CHRONO(espchrono::seconds32)
IMPLEMENT_NVS_GET_SET_CHRONO(espchrono::minutes32)
IMPLEMENT_NVS_GET_SET_CHRONO(espchrono::hours32)
#undef IMPLEMENT_NVS_GET_SET_CHRONO

} // namespace espconfig
