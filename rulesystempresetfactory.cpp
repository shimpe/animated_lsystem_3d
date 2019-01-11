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
    case FLAT_SYSTEM:
    {
        rs.setAxiom("FX");
        rs.addRule(Rule("X","X+YF+"));
        rs.addRule(Rule("Y","-FX-C2YC0"));
        rs.setNoOfIterations(NoOfIterations == -1 ? 10 : NoOfIterations);

        rh.setInitialSegmentLength(1.0);
        rh.setInitialSegmentThickness(0.2);
        rh.setInitialSegmentLengthExpansion(0.5);
        rh.setInitialSegmentThicknessExpansion(0.3);
        rh.setInitialJointExpansion(1.0);
        rh.setInitialAngles(getRecommendedAngles(type));
        QMap<QChar, QColor> customColorTable;
        customColorTable['0'] = "brown";
        customColorTable['1'] = "yellow";
        customColorTable['2'] = "green";
        rh.setColorTable(customColorTable);
    }
        break;
    case SPHERICAL:
    {
        rs.setAxiom("C0X+C1X+C2X+C3X+C4X");
        rs.addRule(Rule("X","[X-X-X-X]^"));
        rs.setNoOfIterations(NoOfIterations == -1 ? 3 : NoOfIterations);

        rh.setInitialSegmentLength(1.0);
        rh.setInitialSegmentThickness(0.1);
        rh.setInitialSegmentLengthExpansion(0.3);
        rh.setInitialSegmentThicknessExpansion(0.3);
        rh.setInitialJointExpansion(1.0);
        rh.setInitialAngles(getRecommendedAngles(type));
        QMap<QChar, QColor> customColorTable;
        customColorTable['0'] = "brown";
        customColorTable['1'] = "yellow";
        customColorTable['2'] = "green";
        customColorTable['2'] = "blue";
        customColorTable['2'] = "black";
        rh.setColorTable(customColorTable);
    }

    }
    return LSystemPreset(rs, rh);
}

std::tuple<double, double, double> RuleSystemPresetFactory::getRecommendedAngles(RSP type) const
{
    switch(type)
    {
    case FLAT_SYSTEM:
        return std::make_tuple(72.0, 72.0, 72.0);
    case SPHERICAL:
        return std::make_tuple(80.0, 80.0, 80.0);
    }
    return std::make_tuple(0.0, 0.0, 0.0);
}
