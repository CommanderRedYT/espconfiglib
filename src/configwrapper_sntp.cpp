#include "configutils_sntp.h"
#include "espstrutils.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::espcpputils::toString;
#include "configwrapper_priv.h"

namespace espconfig {
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(sntp_sync_mode_t)
} // namespace espconfig
