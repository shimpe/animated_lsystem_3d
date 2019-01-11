#ifndef RENDERHINTS_H
#define RENDERHINTS_H

#include <QVector3D>
#include <QMap>
#include <QChar>
#include <QColor>

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

    void setInitialPosition(const QVector3D &initPos);
    const QVector3D &initialPosition() const;

    void setInitialBasis(const QVector3D &x, const QVector3D &y, const QVector3D &z);
    const QVector3D &initialXDir() const;
    const QVector3D &initialYDir() const;
    const QVector3D &initialZDir() const;

    void setColorTable(const QMap<QChar, QColor> &colorTable);
    QColor getColor(const QChar &c) const;

private:
    double m_initialSegmentLength;
    double m_initialSegmentLengthExpansion;
    double m_initialSegmentThickness;
    double m_initialSegmentThicknessExpansion;
    double m_initialJointExpansion;
    double m_initialTurnAngle;
    double m_initialRollAngle;
    double m_initialPitchAngle;
    QVector3D m_initialPosition;
    QVector3D m_initialXDir;
    QVector3D m_initialYDir;
    QVector3D m_initialZDir;
    QMap<QChar, QColor> m_colorTable;
};

#endif // RENDERHINTS_H
