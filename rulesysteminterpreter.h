#ifndef RULESYSTEMINTERPRETER_H
#define RULESYSTEMINTERPRETER_H

#include <QMatrix3x3>
#include <QObject>
#include <QVector3D>
#include <QStack>

#include "QQmlObjectListModel.h"
#include "pipe3d.h"
#include "renderhints.h"

class RuleSystemInterpreter : public QObject
{
    Q_OBJECT
public:
    explicit RuleSystemInterpreter(QObject *parent = nullptr);

    Q_INVOKABLE void setCalculatedString(const QString &str);

    Q_INVOKABLE int noOfPipes();
    Q_INVOKABLE QVector3D getFrom(int pipeidx);
    Q_INVOKABLE QVector3D getTo(int pipeidx);
    Q_INVOKABLE double w(int pipeidx);
    Q_INVOKABLE double h(int pipeidx);
    Q_INVOKABLE double d(int pipeidx);
    Q_INVOKABLE double l(int pipeidx);
    Q_INVOKABLE double lxz(int pipeidx);
    Q_INVOKABLE double tx(int pipeidx);
    Q_INVOKABLE double ty(int pipeidx);
    Q_INVOKABLE double tz(int pipeidx);
    Q_INVOKABLE double anglex(int pipeidx);
    Q_INVOKABLE double angley(int pipeidx);
    Q_INVOKABLE double thickness(int pipeidx);

    Q_INVOKABLE void setAnglesInDegree(double turnangle_degree, double rollangle_degree, double pitchangle_degree);

    Q_INVOKABLE bool refresh() const;

public:
    QQmlObjectListModel<Pipe3D>& getPipes() {
        if (!m_cacheUpToDate)
            recalculate();
        return m_3dPipes;
    }
    RenderHints &getRenderHints() {
        return m_renderHints;
    }
    void setRenderHints(const RenderHints &rh);

    void recalculate();

signals:
    void refreshChanged();

private:
    QQmlObjectListModel<Pipe3D> m_3dPipes;
    QString m_calculatedString;

    bool m_cacheUpToDate;
    double m_turnAngleInDegree;
    double m_rollAngleInDegree;
    double m_pitchAngleInDegree;
    double m_turnAngleInRadians;
    double m_rollAngleInRadians;
    double m_pitchAngleInRadians;
    QMatrix3x3 m_turnLeftRotationMatrix;
    QMatrix3x3 m_turnRightRotationMatrix;
    QMatrix3x3 m_rollLeftRotationMatrix;
    QMatrix3x3 m_rollRightRotationMatrix;
    QMatrix3x3 m_pitchLeftRotationMatrix;
    QMatrix3x3 m_pitchRightRotationMatrix;

    bool m_refresh;
    void setrefresh(bool parameter);

    QVector3D m_xdir;
    QVector3D m_ydir;
    QVector3D m_zdir;
    QVector3D m_pos;

    double m_segmentLength;
    double m_segmentLengthExpansion;
    double m_segmentThickness;
    double m_segmentThicknessExpansion;

    QStack<double> m_stackTurnAngle;
    QStack<double> m_stackRollAngle;
    QStack<double> m_stackPitchAngle;
    QStack<double> m_stackSegmentLength;
    QStack<double> m_stackSegmentThickness;
    QStack<QVector3D> m_stackxdir;
    QStack<QVector3D> m_stackydir;
    QStack<QVector3D> m_stackzdir;
    QStack<QVector3D> m_stackPos;

    RenderHints m_renderHints;

    void updateBasis(const QMatrix3x3 &matrix);

signals:

public slots:
};

#endif // RULESYSTEMINTERPRETER_H
