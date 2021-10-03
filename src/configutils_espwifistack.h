#pragma once

// esp-idf includes
#include <nvs.h>

// local includes
#include "configutils_base.h"
#include "espwifiutils.h"

namespace espconfig {

inline esp_err_t nvs_get(nvs_handle handle, const char* key, wifi_stack::ip_address_t* out_value)
{
    wifi_stack::ip_address_t::value_t temp;
    const auto result = nvs_get(handle, key, &temp);
    if (result == ESP_OK)
        *out_value = wifi_stack::ip_address_t{temp};
    return result;
}



inline esp_err_t nvs_set(nvs_handle handle, const char* key, wifi_stack::ip_address_t value)
{
    return nvs_set(handle, key, value.value());
}

} // namespace espconfig
