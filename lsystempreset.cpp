#include "lsystempreset.h"
#include <QColor>
#include "rule.h"
#include "rulesystem.h"

LSystemPreset::LSystemPreset()
{   
}

LSystemPreset::LSystemPreset(const RuleSystem &RSystem, const RenderHints &RHints)
    : m_RuleSystem(RSystem)
    , m_RenderHints(RHints)
{
}

LSystemPreset::~LSystemPreset()
{
}

RuleSystem &LSystemPreset::ruleSystem()
{
    return m_RuleSystem;
}

RenderHints &LSystemPreset::renderHints()
{
    return m_RenderHints;
}
