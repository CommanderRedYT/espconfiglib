#pragma once

// system includes
#include <string>

// esp-idf includes
#include <nvs.h>

// 3rdparty lib includes
#include <tl/expected.hpp>

// local includes
#include "cppmacros.h"

namespace espconfig {
enum class AllowReset { NoReset, DoReset };
constexpr auto NoReset = AllowReset::NoReset;
constexpr auto DoReset = AllowReset::DoReset;

using ConfigStatusReturnType = tl::expected<void, std::string>;

class ConfigWrapperInterface
{
    CPP_DISABLE_COPY_MOVE(ConfigWrapperInterface)

public:
    ConfigWrapperInterface(AllowReset allowReset, const char *nvsName);
    virtual ~ConfigWrapperInterface() = default;

    virtual const char *type() const = 0;

    virtual std::string valueAsString() const = 0;
    virtual std::string defaultAsString() const = 0;

    virtual ConfigStatusReturnType loadFromFlash(nvs_handle_t nvsHandle) = 0;
    virtual ConfigStatusReturnType reset(nvs_handle_t nvsHandle) = 0;
    virtual ConfigStatusReturnType forceReset(nvs_handle_t nvsHandle) = 0;

    bool allowReset() const { return m_allowReset; }
    const char *nvsName() const { return m_nvsName; }
    bool touched() const { return m_touched; }
    bool loaded() const { return m_loaded; }

protected:
    const bool m_allowReset;
    const char * const m_nvsName;
    bool m_touched{};
    bool m_loaded{};
};

} // namespace espconfig
