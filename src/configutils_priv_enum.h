#pragma once

// system includes
#include <type_traits>
#include <utility>

// esp-idf includes
#include <nvs.h>

// local includes
#include "configutils_base.h"

#define IMPLEMENT_NVS_GET_SET_ENUM(Name) \
    namespace espconfig { \
    inline esp_err_t nvs_get(nvs_handle handle, const char* key, Name* out_value) \
    { \
        std::underlying_type_t<Name> temp; \
        const auto result = nvs_get(handle, key, &temp); \
        if (result == ESP_OK) \
            *out_value = Name(temp); \
        return result; \
    } \
    \
    inline esp_err_t nvs_set(nvs_handle handle, const char* key, Name value) \
    { \
        return nvs_set(handle, key, std::to_underlying(value)); \
    } \
    } // namespace espconfig
