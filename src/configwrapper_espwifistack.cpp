#include "configutils_espwifistack.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::wifi_stack::toString;
#include "configwrapper_priv.h"

namespace espconfig {
using ip_address_t = wifi_stack::ip_address_t;
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(ip_address_t)
} // namespace espconfig
