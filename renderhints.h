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

    double initialJointExpansion() const;
    void setInitialJointExpansion(double initialJointExpansion);

    double initialTurnAngle() const;
    void setInitialTurnAngle(double initialTurnAngle);

    double initialRollAngle() const;
    void setInitialRollAngle(double initialRollAngle);

    double initialPitchAngle() const;
    void setInitialPitchAngle(double initialPitchAngle);

    void setInitialAngles(const std::tuple<double, double, double> &angles);

private:
    double m_initialSegmentLength;
    double m_initialSegmentLengthExpansion;
    double m_initialSegmentThickness;
    double m_initialSegmentThicknessExpansion;
    double m_initialJointExpansion;
    double m_initialTurnAngle;
    double m_initialRollAngle;
    double m_initialPitchAngle;
};

#endif // RENDERHINTS_H
