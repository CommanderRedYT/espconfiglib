#pragma once

// system includes
#include <string>
#include <type_traits>

// 3rdparty lib includes
#include <tl/expected.hpp>

// local includes
#include "configwrapperinterface.h"
#include "cppmacros.h"

namespace espconfig {

using ConfigConstraintReturnType = ConfigStatusReturnType;

template<typename T>
class ConfigWrapper final : public ConfigWrapperInterface
{
    CPP_DISABLE_COPY_MOVE(ConfigWrapper)

    using DefaultValueCallbackRef = T(&)();
    using DefaultValueCallbackPtr = T(*)();

public:
    using value_t = typename std::conditional<std::is_same<T, std::string>::value, const T &, T>::type;
    using ConstraintCallback = ConfigConstraintReturnType(*)(value_t);

    ConfigWrapper(const T &defaultValue, AllowReset allowReset, ConstraintCallback constraintCallback, const char *nvsName);
    ConfigWrapper(T &&defaultValue, AllowReset allowReset, ConstraintCallback constraintCallback, const char *nvsName);
    ConfigWrapper(const ConfigWrapper<T> &factoryConfig, ConstraintCallback constraintCallback, const char *nvsName);
    ConfigWrapper(const DefaultValueCallbackRef &defaultCallback, AllowReset allowReset, ConstraintCallback constraintCallback, const char *nvsName);
    ~ConfigWrapper() override;

    ConfigStatusReturnType write(nvs_handle_t nvsHandle, value_t value);

    const char *type() const override final;

    std::string valueAsString() const override final;
    std::string defaultAsString() const override final;

    T defaultValue() const;

    ConfigStatusReturnType loadFromFlash(nvs_handle_t nvsHandle) override final;
    ConfigStatusReturnType reset(nvs_handle_t nvsHandle) override final;
    ConfigStatusReturnType forceReset(nvs_handle_t nvsHandle) override final;

    ConfigConstraintReturnType checkValue(value_t value) const;

    const T &value() const { return m_value; }

private:
    ConfigStatusReturnType writeToFlash(nvs_handle_t nvsHandle, value_t value);

    T m_value;

    const enum : uint8_t { DefaultByValue, DefaultByFactoryConfig, DefaultByCallback } m_defaultType;

    union
    {
        const T m_defaultValue;
        const ConfigWrapper<T> * const m_factoryConfig;
        const DefaultValueCallbackPtr m_defaultCallback;
    };

    const ConstraintCallback m_constraintCallback;
};

} // namespace espconfig
