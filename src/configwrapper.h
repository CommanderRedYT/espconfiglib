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
class ConfigWrapper : public ConfigWrapperInterface
{
    CPP_DISABLE_COPY_MOVE(ConfigWrapper)

public:
    using DefaultValueCallbackRef = T(&)();
    using DefaultValueCallbackPtr = T(*)();

    using value_t = typename std::conditional<std::is_same<T, std::string>::value, const T &, T>::type;
    using ConstraintCallback = ConfigConstraintReturnType(*)(value_t);

    ConfigWrapper() = default;

    ConfigStatusReturnType write(nvs_handle_t nvsHandle, value_t value);

    const char *type() const override final;

    std::string valueAsString() const override final;
    std::string defaultAsString() const override final;

    virtual T defaultValue() const = 0;

    ConfigStatusReturnType loadFromFlash(nvs_handle_t nvsHandle) override final;
    ConfigStatusReturnType reset(nvs_handle_t nvsHandle) override final;
    ConfigStatusReturnType forceReset(nvs_handle_t nvsHandle) override final;

    virtual ConfigConstraintReturnType checkValue(value_t value) const = 0;

    const T &value() const { return m_value; }

private:
    ConfigStatusReturnType writeToFlash(nvs_handle_t nvsHandle, value_t value);

    T m_value;
};

} // namespace espconfig
