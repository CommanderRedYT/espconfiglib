#include "configutils_espchrono.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::espchrono::toString;
#include "configwrapper_priv.h"

INSTANTIATE_CONFIGWRAPPER_TEMPLATES(espchrono::DayLightSavingMode)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(espchrono::milliseconds32)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(espchrono::seconds32)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(espchrono::minutes32)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(espchrono::hours32)
