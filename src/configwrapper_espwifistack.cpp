#include "configutils_espwifistack.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::wifi_stack::toString;
#include "configwrapper_priv.h"

INSTANTIATE_CONFIGWRAPPER_TEMPLATES(wifi_stack::mac_t)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(std::optional<wifi_stack::mac_t>)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(wifi_stack::ip_address_t)
