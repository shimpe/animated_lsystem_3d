#include "renderhints.h"

RenderHints::RenderHints()
    : m_initialSegmentLength(1.0)
    , m_initialSegmentLengthExpansion(1.0)
    , m_initialSegmentThickness(0.1)
    , m_initialSegmentThicknessExpansion(1.0)
    , m_initialJointExpansion(1.0)
    , m_initialTurnAngle(30)
    , m_initialRollAngle(30)
    , m_initialPitchAngle(30)
    , m_initialPosition(0,0,0)
    , m_initialXDir(1,0,0)
    , m_initialYDir(0,1,0)
    , m_initialZDir(0,0,1)
{
}

double RenderHints::initialSegmentLength() const
{
    return m_initialSegmentLength;
}

void RenderHints::setInitialSegmentLength(double segmentLength)
{
    m_initialSegmentLength = segmentLength;
}

double RenderHints::initialSegmentLengthExpansion() const
{
    return m_initialSegmentLengthExpansion;
}

void RenderHints::setInitialSegmentLengthExpansion(double segmentLengthExpansion)
{
    m_initialSegmentLengthExpansion = segmentLengthExpansion;
}

double RenderHints::initialSegmentThickness() const
{
    return m_initialSegmentThickness;
}

void RenderHints::setInitialSegmentThickness(double segmentThickness)
{
    m_initialSegmentThickness = segmentThickness;
}

double RenderHints::initialSegmentThicknessExpansion() const
{
    return m_initialSegmentThicknessExpansion;
}

void RenderHints::setInitialSegmentThicknessExpansion(double segmentThicknessExpansion)
{
    m_initialSegmentThicknessExpansion = segmentThicknessExpansion;
}

double RenderHints::initialJointExpansion() const
{
    return m_initialJointExpansion;
}

void RenderHints::setInitialJointExpansion(double initialJointExpansion)
{
    m_initialJointExpansion = initialJointExpansion;
}

double RenderHints::initialRollAngle() const
{
    return m_initialRollAngle;
}

void RenderHints::setInitialRollAngle(double initialRollAngle)
{
    m_initialRollAngle = initialRollAngle;
}

double RenderHints::initialPitchAngle() const
{
    return m_initialPitchAngle;
}

void RenderHints::setInitialPitchAngle(double initialPitchAngle)
{
    m_initialPitchAngle = initialPitchAngle;
}

void RenderHints::setInitialAngles(const std::tuple<double, double, double> &angles)
{
    m_initialTurnAngle = std::get<0>(angles);
    m_initialRollAngle = std::get<1>(angles);
    m_initialPitchAngle = std::get<2>(angles);
}

void RenderHints::setInitialPosition(const QVector3D &initPos)
{
    m_initialPosition = initPos;
}

const QVector3D &RenderHints::initialPosition() const
{
    return m_initialPosition;
}

void RenderHints::setInitialBasis(const QVector3D &x, const QVector3D &y, const QVector3D &z)
{
    m_initialXDir = x;
    m_initialYDir = y;
    m_initialZDir = z;
}

const QVector3D &RenderHints::initialXDir() const
{
    return m_initialXDir;
}

const QVector3D &RenderHints::initialYDir() const
{
    return m_initialYDir;
}

const QVector3D &RenderHints::initialZDir() const
{
    return m_initialZDir;
}

double RenderHints::initialTurnAngle() const
{
    return m_initialTurnAngle;
}

void RenderHints::setInitialTurnAngle(double initialTurnAngle)
{
    m_initialTurnAngle = initialTurnAngle;
}
