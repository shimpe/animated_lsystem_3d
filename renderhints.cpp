#include "renderhints.h"

RenderHints::RenderHints()
    : m_initialSegmentLength(1.0)
    , m_initialSegmentLengthExpansion(1.0)
    , m_initialSegmentThickness(0.1)
    , m_initialSegmentThicknessExpansion(1.0)
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
