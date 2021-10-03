#pragma once

#include "sdkconfig.h"
#define LOG_LOCAL_LEVEL CONFIG_LOG_LOCAL_LEVEL_CONFIG

// system includes
#include <utility>
#include <cassert>

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <fmt/core.h>

// local includes
#include "configwrapper.h"
#include "cpputils.h"

#define INSTANTIATE_CONFIGWRAPPER_TEMPLATES(TYPE) \
    namespace espconfig { \
    template ConfigWrapper<TYPE>::ConfigWrapper(const TYPE &defaultValue, AllowReset allowReset, ConstraintCallback constraintCallback, const char *nvsName); \
    template ConfigWrapper<TYPE>::ConfigWrapper(TYPE &&defaultValue, AllowReset allowReset, ConstraintCallback constraintCallback, const char *nvsName); \
    template ConfigWrapper<TYPE>::ConfigWrapper(const ConfigWrapper<TYPE> &factoryConfig, ConstraintCallback constraintCallback, const char *nvsName); \
    template ConfigWrapper<TYPE>::ConfigWrapper(DefaultValueCallbackRef &defaultCallback, AllowReset allowReset, ConstraintCallback constraintCallback, const char *nvsName); \
    template ConfigStatusReturnType ConfigWrapper<TYPE>::write(nvs_handle_t nvsHandle, value_t value); \
    template<> const char *ConfigWrapper<TYPE>::type() const { return #TYPE; } \
    template std::string ConfigWrapper<TYPE>::valueAsString() const; \
    template std::string ConfigWrapper<TYPE>::defaultAsString() const; \
    template TYPE ConfigWrapper<TYPE>::defaultValue() const; \
    template ConfigStatusReturnType ConfigWrapper<TYPE>::loadFromFlash(nvs_handle_t nvsHandle); \
    template ConfigStatusReturnType ConfigWrapper<TYPE>::reset(nvs_handle_t nvsHandle); \
    template ConfigStatusReturnType ConfigWrapper<TYPE>::forceReset(nvs_handle_t nvsHandle); \
    template ConfigConstraintReturnType ConfigWrapper<TYPE>::checkValue(value_t value) const; \
    template ConfigStatusReturnType ConfigWrapper<TYPE>::writeToFlash(nvs_handle_t nvsHandle, value_t value); \
    } // namespace espconfig

namespace espconfig {
namespace {
constexpr const char * const TAG = "CONFIG";
} // namespace

template<typename T>
ConfigWrapper<T>::ConfigWrapper(const T &defaultValue, AllowReset allowReset, ConstraintCallback constraintCallback, const char *nvsName) :
    ConfigWrapperInterface{allowReset, nvsName},
    m_defaultType{DefaultByValue},
    m_defaultValue{defaultValue},
    m_constraintCallback{constraintCallback}
{
}

template<typename T>
ConfigWrapper<T>::ConfigWrapper(T &&defaultValue, AllowReset allowReset, ConstraintCallback constraintCallback, const char *nvsName) :
    ConfigWrapperInterface{allowReset, nvsName},
    m_defaultType{DefaultByValue},
    m_defaultValue{std::move(defaultValue)},
    m_constraintCallback{constraintCallback}
{
}

template<typename T>
ConfigWrapper<T>::ConfigWrapper(const ConfigWrapper<T> &factoryConfig, ConstraintCallback constraintCallback, const char *nvsName) :
    ConfigWrapperInterface{AllowReset::DoReset, nvsName},
    m_defaultType{DefaultByFactoryConfig},
    m_factoryConfig{&factoryConfig},
    m_constraintCallback{constraintCallback}
{
}

template<typename T>
ConfigWrapper<T>::ConfigWrapper(const DefaultValueCallbackRef &defaultCallback, AllowReset allowReset, ConstraintCallback constraintCallback, const char *nvsName) :
    ConfigWrapperInterface{allowReset, nvsName},
    m_defaultType{DefaultByCallback},
    m_defaultCallback{&defaultCallback},
    m_constraintCallback{constraintCallback}
{
}

template<typename T>
ConfigWrapper<T>::~ConfigWrapper()
{
    switch (m_defaultType)
    {
    case DefaultByValue:         m_defaultValue.~T(); break;
    case DefaultByFactoryConfig: /*m_factoryConfig.~typeof(m_factoryConfig)();*/ break;
    case DefaultByCallback:      /*m_defaultCallback.~typeof(m_defaultCallback)();*/ break;
    }
}

template<typename T>
ConfigStatusReturnType ConfigWrapper<T>::write(nvs_handle_t nvsHandle, value_t value)
{
    CONFIGWRAPPER_TOSTRING_USINGS

    ESP_LOGD(TAG, "%s %s", m_nvsName, toString(value).c_str());

    if (!m_loaded)
        ESP_LOGE(TAG, "%s has not been loaded yet!", m_nvsName);

    if (const auto result = checkValue(value); !result)
    {
        ESP_LOGW(TAG, "%s cannot be set to %s: constraint not met: %s", m_nvsName, toString(value).c_str(), result.error().c_str());
        return result;
    }

    if (m_value == value)
        return {};

    return writeToFlash(nvsHandle, value);
}

template<typename T>
std::string ConfigWrapper<T>::valueAsString() const
{
    CONFIGWRAPPER_TOSTRING_USINGS

    if (m_touched)
        return toString(m_value);
    else
        return "--not-touched-- " + toString(m_value);
}

template<typename T>
std::string ConfigWrapper<T>::defaultAsString() const
{
    CONFIGWRAPPER_TOSTRING_USINGS

    return toString(defaultValue());
}

template<typename T>
T ConfigWrapper<T>::defaultValue() const
{
    switch (m_defaultType)
    {
    case DefaultByValue:         return m_defaultValue;
    case DefaultByFactoryConfig: assert(m_factoryConfig->m_loaded); return m_factoryConfig->value;
    case DefaultByCallback:      return m_defaultCallback();
    }

    __builtin_unreachable();
}

template<typename T>
ConfigStatusReturnType ConfigWrapper<T>::loadFromFlash(nvs_handle_t nvsHandle)
{
    //ESP_LOGD(TAG, "%s", m_nvsName);

    const auto result = nvs_get(nvsHandle, m_nvsName, &m_value);

    ESP_LOG_LEVEL_LOCAL((cpputils::is_in(result, ESP_OK, ESP_ERR_NVS_NOT_FOUND) ? ESP_LOG_DEBUG : ESP_LOG_ERROR), TAG, "%s nvs_get() returned: %s", m_nvsName, esp_err_to_name(result));

    if (result == ESP_OK)
    {
        if (const auto result = checkValue(m_value); !result)
        {
            ESP_LOGE(TAG, "%s constraint not met for value in flash: %s", m_nvsName, result.error().c_str());
            return forceReset(nvsHandle);
        }

        m_loaded = true;
        m_touched = true;
        return {};
    }
    else if (result == ESP_ERR_NVS_NOT_FOUND)
    {
        m_loaded = true;
        m_touched = false;
        m_value = defaultValue();
        if (const auto result = checkValue(m_value); !result)
            ESP_LOGE(TAG, "%s constraint not met for value from default: %s", m_nvsName, result.error().c_str());

        return {};
    }
    else
    {
        return forceReset(nvsHandle);
    }
}

template<typename T>
ConfigStatusReturnType ConfigWrapper<T>::reset(nvs_handle_t nvsHandle)
{
    ESP_LOGD(TAG, "%s", m_nvsName);

    if (!m_allowReset)
        return {};

    return forceReset(nvsHandle);
}

template<typename T>
ConfigStatusReturnType ConfigWrapper<T>::forceReset(nvs_handle_t nvsHandle)
{
    ESP_LOGD(TAG, "%s", m_nvsName);

    auto result = nvs_erase_key(nvsHandle, m_nvsName);

    ESP_LOG_LEVEL_LOCAL((cpputils::is_in(result, ESP_OK, ESP_ERR_NVS_NOT_FOUND) ? ESP_LOG_DEBUG : ESP_LOG_ERROR), TAG, "%s nvs_erase_key() returned: %s", m_nvsName, esp_err_to_name(result));

    if (result == ESP_ERR_NVS_NOT_FOUND)
    {
        if (m_touched)
            ESP_LOGE(TAG, "%s for touched and not found?!", m_nvsName);
        result = ESP_OK;
    }

    if (result == ESP_OK || !m_loaded)
    {
        if (!m_loaded /* && result == ESP_OK */)
            m_loaded = true;
        m_touched = false;
        m_value = defaultValue();
    }

    if (result != ESP_OK)
        return tl::make_unexpected(std::string{"nvs_erase_key() failed with "} + esp_err_to_name(result));

    return {};
}

template<typename T>
ConfigConstraintReturnType ConfigWrapper<T>::checkValue(value_t value) const
{
    if (!m_constraintCallback)
        return {};

    return m_constraintCallback(value);
}

template<typename T>
ConfigStatusReturnType ConfigWrapper<T>::writeToFlash(nvs_handle_t nvsHandle, value_t value)
{
    CONFIGWRAPPER_TOSTRING_USINGS

    ESP_LOGD(TAG, "%s %s", m_nvsName, toString(value).c_str());

    const auto result = nvs_set(nvsHandle, m_nvsName, value);

    ESP_LOG_LEVEL_LOCAL((result == ESP_OK ? ESP_LOG_INFO : ESP_LOG_ERROR), TAG, "%s %s nvs_set() returned %s", m_nvsName, toString(value).c_str(), esp_err_to_name(result));

    m_value = value;
    m_touched = true;

    if (result != ESP_OK)
        return tl::make_unexpected(std::string{"nvs_set() failed with "} + esp_err_to_name(result));
    return {};
}

} // namespace espconfig
