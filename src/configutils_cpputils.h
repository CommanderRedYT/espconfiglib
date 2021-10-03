#pragma once

// esp-idf includes
#include <nvs.h>

// local includes
#include "configutils_base.h"
#include "color_utils.h"

namespace espconfig {

inline esp_err_t nvs_get(nvs_handle handle, const char* key, cpputils::ColorHelper* out_value)
{
    uint32_t temp;
    const auto result = nvs_get(handle, key, &temp);
    if (result == ESP_OK)
        *out_value = cpputils::numberToColor(temp);
    return result;
}



inline esp_err_t nvs_set(nvs_handle handle, const char* key, cpputils::ColorHelper value)
{
    return nvs_set(handle, key, cpputils::colorToNumber(value));
}

} // namespace espconfig
