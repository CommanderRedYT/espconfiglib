#include "configutils_cpputils.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::cpputils::toString;
#include "configwrapper_priv.h"

namespace espconfig {
using ColorHelper = cpputils::ColorHelper;
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(ColorHelper)
} // namespace espconfig
