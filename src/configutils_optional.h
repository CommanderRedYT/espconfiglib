#pragma once

// system includes
#include <optional>
#include <cstdint>

// esp-idf includes
#include <nvs.h>

// local includes
#include "configutils_base.h"

namespace espconfig {

template<typename T>
esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<T>* out_value)
{
    size_t length;
    if (const esp_err_t result = nvs_get_blob(handle, key, nullptr, &length); result != ESP_OK)
        return result;

    struct Pair { T value; bool valid; };
    union { Pair pair; char buf[sizeof(Pair)]; };

    if (length != sizeof(Pair))
    {
        //ESP_LOGW(TAG, "invalid size of optional, expected=%u actual=&zd", sizeof(Pair), length);
        return ESP_ERR_INVALID_SIZE;
    }

    if (const esp_err_t result = nvs_get_blob(handle, key, buf, &length); result != ESP_OK)
        return result;

    if (pair.valid)
        *out_value = pair.value;
    else
        *out_value = std::nullopt;

    return ESP_OK;
}

template esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<int8_t>* out_value);
template esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<uint8_t>* out_value);
template esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<int16_t>* out_value);
template esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<uint16_t>* out_value);
template esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<int32_t>* out_value);
template esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<uint32_t>* out_value);
template esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<int64_t>* out_value);
template esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<uint64_t>* out_value);
template esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<float>* out_value);
template esp_err_t nvs_get(nvs_handle handle, const char* key, std::optional<double>* out_value);



template<typename T>
esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<T> value)
{
    struct Pair { T value; bool valid; };
    union { Pair pair; char buf[sizeof(Pair)]; };

    if (value)
    {
        pair.valid = true;
        pair.value = *value;
    }
    else
        pair.valid = false;

    return nvs_set_blob(handle, key, buf, sizeof(buf));
}

template esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<int8_t> value);
template esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<uint8_t> value);
template esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<int16_t> value);
template esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<uint16_t> value);
template esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<int32_t> value);
template esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<uint32_t> value);
template esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<int64_t> value);
template esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<uint64_t> value);
template esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<float> value);
template esp_err_t nvs_set(nvs_handle handle, const char* key, std::optional<double> value);

} // namespace espconfig
