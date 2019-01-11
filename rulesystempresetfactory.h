#ifndef RULESYSTEMPRESET_H
#define RULESYSTEMPRESET_H

#include "lsystempreset.h"
#include <tuple>

enum RSP {
    FLAT_SYSTEM,
    SPHERICAL
};

class RuleSystemPresetFactory
{
public:
    RuleSystemPresetFactory();
    LSystemPreset createRuleSystemPreset(RSP type, int NoOfIterations=-1); // -1 uses a default value
    std::tuple<double, double, double> getRecommendedAngles(RSP type) const;
};

#endif // RULESYSTEMPRESET_H
