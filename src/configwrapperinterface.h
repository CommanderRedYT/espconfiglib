#pragma once

// system includes
#include <string>
#include <expected>

// esp-idf includes
#include <nvs.h>

// local includes
#include "cppmacros.h"

namespace espconfig {

using ConfigStatusReturnType = std::expected<void, std::string>;

class ConfigWrapperInterface
{
    CPP_DISABLE_COPY_MOVE(ConfigWrapperInterface)

public:
    ConfigWrapperInterface() = default;
    virtual ~ConfigWrapperInterface() = default;

    virtual const char *type() const = 0;

    virtual std::string valueAsString() const = 0;
    virtual std::string defaultAsString() const = 0;

    virtual ConfigStatusReturnType loadFromFlash(nvs_handle_t nvsHandle) = 0;
    virtual ConfigStatusReturnType reset(nvs_handle_t nvsHandle) = 0;
    virtual ConfigStatusReturnType forceReset(nvs_handle_t nvsHandle) = 0;

    virtual bool allowReset() const = 0;
    virtual const char *nvsName() const = 0;
    bool touched() const { return m_touched; }
    bool loaded() const { return m_loaded; }

protected:
    bool m_touched{};
    bool m_loaded{};
};

} // namespace espconfig
