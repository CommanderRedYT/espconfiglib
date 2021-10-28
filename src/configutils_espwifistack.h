#pragma once

// system includes
#include <optional>
#include <algorithm>
#include <cstdint>

// esp-idf includes
#include <nvs.h>
#include <esp_wifi_types.h>

// local includes
#include "configutils_base.h"
#include "configutils_priv_enum.h"
#include "espwifiutils.h"

IMPLEMENT_NVS_GET_SET_ENUM(wifi_auth_mode_t)

namespace espconfig {

inline esp_err_t nvs_get(nvs_handle handle, const char* key, wifi_stack::mac_t* out_value)
{
    union {
        uint64_t raw_value;
        std::array<uint8_t, 8> bytes;
        static_assert(sizeof(raw_value) == sizeof(bytes));
    };

    const auto result = nvs_get(handle, key, &raw_value);
    if (result == ESP_OK)
    {
        if (bytes[6] != 0x00 || bytes[7] != 0x00)
            return ESP_ERR_INVALID_MAC;
        std::copy(std::cbegin(bytes), std::cbegin(bytes) + wifi_stack::mac_t::static_size, std::begin(*out_value));
    }
    return result;
}

inline esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<wifi_stack::mac_t>* out_value)
{
    union {
        uint64_t raw_value;
        struct {
            bool valid;
            std::array<uint8_t, 7> bytes;
        } combined;
        static_assert(sizeof(raw_value) == sizeof(combined));
    };

    const auto result = nvs_get(handle, key, &raw_value);
    if (result == ESP_OK)
    {
        if (combined.valid)
        {
            if (combined.bytes[6] != 0x00)
                return ESP_ERR_INVALID_MAC;

            *out_value = wifi_stack::mac_t{};
            std::copy(std::cbegin(combined.bytes), std::cbegin(combined.bytes) + wifi_stack::mac_t::static_size, std::begin(**out_value));
        }
        else
            *out_value = std::nullopt;
    }
    return result;
}

inline esp_err_t nvs_get(nvs_handle handle, const char* key, wifi_stack::ip_address_t* out_value)
{
    wifi_stack::ip_address_t::value_t temp;
    const auto result = nvs_get(handle, key, &temp);
    if (result == ESP_OK)
        *out_value = wifi_stack::ip_address_t{temp};
    return result;
}



inline esp_err_t nvs_set(nvs_handle handle, const char* key, const wifi_stack::mac_t &value)
{
    union {
        uint64_t raw_value;
        std::array<uint8_t, 8> bytes;
        static_assert(sizeof(raw_value) == sizeof(bytes));
    };
    std::copy(std::begin(value), std::end(value), std::begin(bytes));
    bytes[6] = 0x00;
    bytes[7] = 0x00;
    return nvs_set(handle, key, raw_value);
}

inline esp_err_t nvs_set(nvs_handle handle, const char* key, const std::optional<wifi_stack::mac_t> &value)
{
    union {
        uint64_t raw_value;
        struct {
            bool valid;
            std::array<uint8_t, 7> bytes;
        } combined;
        static_assert(sizeof(raw_value) == sizeof(combined));
    };

    if (value)
    {
        combined.valid = true;
        std::copy(std::begin(*value), std::end(*value), std::begin(combined.bytes));
        combined.bytes[6] = 0x00;
    }
    else
        combined.valid = false;

    return nvs_set(handle, key, raw_value);
}

inline esp_err_t nvs_set(nvs_handle handle, const char* key, wifi_stack::ip_address_t value)
{
    return nvs_set(handle, key, value.value());
}

} // namespace espconfig
