#include "rulesystempresetfactory.h"
#include <QColor>
#include "renderhints.h"
#include "rule.h"
#include <QMap>
#include <QChar>

RuleSystemPresetFactory::RuleSystemPresetFactory()
{
}

LSystemPreset RuleSystemPresetFactory::createRuleSystemPreset(RSP type, int NoOfIterations)
{
    RuleSystem rs;
    RenderHints rh;
    switch (type)
    {
        case FIRST_SYSTEM:
        {
            rs.setAxiom("FX");
            rs.addRule(Rule("X","X+YF+"));
            rs.addRule(Rule("Y","-FX-Y"));
            rs.setNoOfIterations(NoOfIterations == -1 ? 10 : NoOfIterations);

            rh.setInitialSegmentLength(1.0);
            rh.setInitialSegmentThickness(0.2);
            rh.setInitialSegmentLengthExpansion(0.5);
            rh.setInitialSegmentThicknessExpansion(0.3);
            rh.setInitialJointExpansion(1.0);
            rh.setInitialAngles(getRecommendedAngles(type));
       }

        break;

    }
    return LSystemPreset(rs, rh);
}

std::tuple<double, double, double> RuleSystemPresetFactory::getRecommendedAngles(RSP type) const
{
    switch(type)
    {
        case FIRST_SYSTEM:
            return std::make_tuple(72.0, 72.0, 72.0);
    }
    return std::make_tuple(0.0, 0.0, 0.0);
}
