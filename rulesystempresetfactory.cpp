#include "rulesystempreset.h"
#include <QColor>
#include "rule.h"
#include <QMap>
#include <QChar>

RuleSystemPresetFactory::RuleSystemPresetFactory()
{
}

LSystemPreset RuleSystemPresetFactory::CreateRuleSystemPreset(RSP type, int NoOfIterations)
{
    RuleSystem rs;
    switch (type)
    {
        case FIRST_SYSTEM:
        {
            rs.setAxiom("FX");
            rs.addRule(Rule("X","X+YF+"));
            rs.addRule(Rule("Y","-FX-Y"));
            rs.setNoOfIterations(NoOfIterations == -1 ? 12 : NoOfIterations);
        }
        break;

    }
    return LSystemPreset(rs);
}

double RuleSystemPresetFactory::getRecommendedAngle(RSP type) const
{
    switch(type)
    {
        case FIRST_SYSTEM:
            return 90;
    }
    return 0.0;
}
