#include "configutils_base.h"
#include "strutils.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::cpputils::toString;
#include "configwrapper_priv.h"

INSTANTIATE_CONFIGWRAPPER_TEMPLATES(bool)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(uint8_t)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(int8_t)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(uint16_t)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(int16_t)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(uint32_t)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(int32_t)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(int)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(uint64_t)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(int64_t)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(float)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(double)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::string)
