#ifndef RENDERHINTS_H
#define RENDERHINTS_H

#include <QObject>
#include "QQmlVarPropertyHelpers.h"

class RenderHints
{
public:
    RenderHints();
    ~RenderHints() {}

    double initialSegmentLength() const;
    void setInitialSegmentLength(double initialSegmentLength);

    double initialSegmentLengthExpansion() const;
    void setInitialSegmentLengthExpansion(double initialSegmentLengthExpansion);

    double initialSegmentThickness() const;
    void setInitialSegmentThickness(double initialSegmentThickness);

    double initialSegmentThicknessExpansion() const;
    void setInitialSegmentThicknessExpansion(double initialSegmentThicknessExpansion);

private:
    double m_initialSegmentLength;
    double m_initialSegmentLengthExpansion;
    double m_initialSegmentThickness;
    double m_initialSegmentThicknessExpansion;
};

#endif // RENDERHINTS_H
