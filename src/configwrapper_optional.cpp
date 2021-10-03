#include "configutils_optional.h"
#include "strutils.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::cpputils::toString;
#include "configwrapper_priv.h"

namespace espconfig {

INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<int8_t>)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<uint8_t>)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<int16_t>)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<uint16_t>)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<int32_t>)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<uint32_t>)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<int64_t>)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<uint64_t>)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<float>)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<double>)

} // namespace espconfig