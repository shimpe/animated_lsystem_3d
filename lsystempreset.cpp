#include "lsystempreset.h"
#include <QColor>
#include "rule.h"
#include "rulesystem.h"

LSystemPreset::LSystemPreset()
{   
}

LSystemPreset::LSystemPreset(const RuleSystem &RSystem)
    : m_RuleSystem(RSystem)
{
}

LSystemPreset::~LSystemPreset()
{
}

RuleSystem &LSystemPreset::ruleSystem()
{
    return m_RuleSystem;
}
