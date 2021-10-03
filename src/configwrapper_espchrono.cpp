#include "configutils_espchrono.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::espchrono::toString;
#include "configwrapper_priv.h"

namespace espconfig {

using DayLightSavingMode = espchrono::DayLightSavingMode;
using milliseconds32 = espchrono::milliseconds32;
using seconds32 = espchrono::seconds32;
using minutes32 = espchrono::minutes32;
using hours32 = espchrono::hours32;

INSTANTIATE_CONFIGWRAPPER_TEMPLATES(espchrono::DayLightSavingMode)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(espchrono::milliseconds32)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(espchrono::seconds32)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(espchrono::minutes32)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(espchrono::hours32)

} // namespace espconfig
