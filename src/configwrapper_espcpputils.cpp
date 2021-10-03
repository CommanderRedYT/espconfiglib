#include "configutils_espcpputils.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::espcpputils::toString;
#include "configwrapper_priv.h"

namespace espconfig {
using CoreAffinity = espcpputils::CoreAffinity;
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(CoreAffinity)
} // namespace espconfig
