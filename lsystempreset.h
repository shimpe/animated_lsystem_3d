#ifndef LSYSTEMPRESET_H
#define LSYSTEMPRESET_H

#include "rulesystem.h"

class LSystemPreset
{
public:
    LSystemPreset();
    LSystemPreset(const RuleSystem &RuleSystem);
    ~LSystemPreset();

    RuleSystem &ruleSystem();

private:
    RuleSystem m_RuleSystem;
};

#endif // LSYSTEMPRESET_H
