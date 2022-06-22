#pragma once

// system includes
#include <cstdint>
#include <string>
#include <bit>

// esp-idf includes
#include <nvs.h>

namespace espconfig {

inline esp_err_t nvs_get(nvs_handle handle, const char* key, int8_t* out_value)  { return nvs_get_i8 (handle, key, out_value); }
inline esp_err_t nvs_get(nvs_handle handle, const char* key, uint8_t* out_value) { return nvs_get_u8 (handle, key, out_value); }
//inline esp_err_t nvs_get(nvs_handle handle, const char* key, char* out_value)    { return nvs_get_i8 (handle, key, (int8_t*)out_value); }
//inline esp_err_t nvs_get(nvs_handle handle, const char* key, unsigned char* out_value) { return nvs_get_u8 (handle, key, (uint8_t*)out_value); }
inline esp_err_t nvs_get(nvs_handle handle, const char* key, int16_t* out_value) { return nvs_get_i16(handle, key, out_value); }
inline esp_err_t nvs_get(nvs_handle handle, const char* key, uint16_t* out_value){ return nvs_get_u16(handle, key, out_value); }
inline esp_err_t nvs_get(nvs_handle handle, const char* key, int32_t* out_value) { return nvs_get_i32(handle, key, out_value); }
inline esp_err_t nvs_get(nvs_handle handle, const char* key, uint32_t* out_value){ return nvs_get_u32(handle, key, out_value); }
inline esp_err_t nvs_get(nvs_handle handle, const char* key, int* out_value) { return nvs_get_i32(handle, key, (int32_t*)out_value); }
inline esp_err_t nvs_get(nvs_handle handle, const char* key, unsigned int* out_value){ return nvs_get_u32(handle, key, (uint32_t*)out_value); }
inline esp_err_t nvs_get(nvs_handle handle, const char* key, int64_t* out_value) { return nvs_get_i64(handle, key, out_value); }
inline esp_err_t nvs_get(nvs_handle handle, const char* key, uint64_t* out_value){ return nvs_get_u64(handle, key, out_value); }
inline esp_err_t nvs_get(nvs_handle handle, const char* key, bool* out_value)
{
    uint8_t temp;
    const auto result = nvs_get(handle, key, &temp);
    if (result == ESP_OK && out_value)
        *out_value = temp;
    return result;
}
inline esp_err_t nvs_get(nvs_handle handle, const char* key, float* out_value)
{
    uint32_t temp;
    const auto result = nvs_get(handle, key, &temp);
    if (result == ESP_OK)
        *out_value = std::bit_cast<float>(temp);
    return result;
}
inline esp_err_t nvs_get(nvs_handle handle, const char* key, double* out_value)
{
    uint64_t temp;
    const auto result = nvs_get(handle, key, &temp);
    if (result == ESP_OK)
        *out_value = std::bit_cast<double>(temp);
    return result;
}
inline esp_err_t nvs_get(nvs_handle handle, const char* key, std::string* out_value)
{
    size_t length;
    if (const esp_err_t result = nvs_get_str(handle, key, nullptr, &length); result != ESP_OK)
        return result;

    char buf[length];
    if (const esp_err_t result = nvs_get_str(handle, key, buf, &length); result != ESP_OK)
        return result;

    *out_value = buf;

    return ESP_OK;
}



inline esp_err_t nvs_set(nvs_handle handle, const char* key, int8_t value)                    { return nvs_set_i8 (handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, uint8_t value)                   { return nvs_set_u8 (handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, int16_t value)                   { return nvs_set_i16(handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, uint16_t value)                  { return nvs_set_u16(handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, int32_t value)                   { return nvs_set_i32(handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, uint32_t value)                  { return nvs_set_u32(handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, int value)                       { return nvs_set_i32(handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, unsigned int value)              { return nvs_set_u32(handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, const int64_t &value)            { return nvs_set_i64(handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, const uint64_t &value)           { return nvs_set_u64(handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, bool value)                      { return nvs_set_u8 (handle, key, value); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, float value)                     { return nvs_set(handle, key, std::bit_cast<uint32_t>(value)); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, const double &value)             { return nvs_set(handle, key, std::bit_cast<uint64_t>(value)); }
inline esp_err_t nvs_set(nvs_handle handle, const char* key, const std::string &value)        { return nvs_set_str(handle, key, value.c_str()); }

} // namespace espconfig
