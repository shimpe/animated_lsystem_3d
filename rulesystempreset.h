#ifndef RULESYSTEMPRESET_H
#define RULESYSTEMPRESET_H

#include "lsystempreset.h"

enum RSP {
    FIRST_SYSTEM,
};

class RuleSystemPresetFactory
{
public:
    RuleSystemPresetFactory();
    LSystemPreset CreateRuleSystemPreset(RSP type, int NoOfIterations=-1); // -1 uses a default value
    double getRecommendedAngle(RSP type) const;
};

#endif // RULESYSTEMPRESET_H
