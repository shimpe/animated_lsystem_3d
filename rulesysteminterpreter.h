#ifndef RULESYSTEMINTERPRETER_H
#define RULESYSTEMINTERPRETER_H

#include <QMatrix3x3>
#include <QObject>
#include <QVector3D>
#include <QStack>

#include "QQmlObjectListModel.h"
#include "pipe3d.h"

class RuleSystemInterpreter : public QObject
{
    Q_OBJECT
public:
    explicit RuleSystemInterpreter(QObject *parent = nullptr);

    Q_INVOKABLE void setCalculatedString(const QString &str);
    Q_INVOKABLE void setSegmentLength(double len);
    Q_INVOKABLE void setSegmentLengthContraction(double lenContraction);
    Q_INVOKABLE void setSegmentThickness(double thickness);
    Q_INVOKABLE void setSegmentThicknessContraction(double thicknessContraction);
    Q_INVOKABLE double segmentLength() const;
    Q_INVOKABLE double segmentLengthContraction() const;
    Q_INVOKABLE double segmentThickness() const;
    Q_INVOKABLE double segmentThicknessContraction() const;


    Q_INVOKABLE int noOfPipes() const;
    Q_INVOKABLE QVector3D getFrom(int pipeidx) const;
    Q_INVOKABLE QVector3D getTo(int pipeidx) const;
    Q_INVOKABLE double w(int pipeidx) const;
    Q_INVOKABLE double h(int pipeidx) const;
    Q_INVOKABLE double d(int pipeidx) const;
    Q_INVOKABLE double l(int pipeidx) const;
    Q_INVOKABLE double lxz(int pipeidx) const;
    Q_INVOKABLE double tx(int pipeidx) const;
    Q_INVOKABLE double ty(int pipeidx) const;
    Q_INVOKABLE double tz(int pipeidx) const;
    Q_INVOKABLE double anglex(int pipeidx) const;
    Q_INVOKABLE double angley(int pipeidx) const;
    Q_INVOKABLE double thickness(int pipeidx) const;

    Q_INVOKABLE void setAnglesInDegree(double turnangle_degree, double rollangle_degree, double pitchangle_degree);

    Q_INVOKABLE bool refresh() const;

public:
    QQmlObjectListModel<Pipe3D>& getPipes() { return m_3dPipes; }

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
    double m_segmentLengthContraction;
    double m_segmentThickness;
    double m_segmentThicknessContraction;

    QStack<double> m_stackTurnAngle;
    QStack<double> m_stackRollAngle;
    QStack<double> m_stackPitchAngle;
    QStack<double> m_stackSegmentLength;
    QStack<double> m_stackSegmentThickness;
    QStack<QVector3D> m_stackxdir;
    QStack<QVector3D> m_stackydir;
    QStack<QVector3D> m_stackzdir;
    QStack<QVector3D> m_stackPos;

    void updateBasis(const QMatrix3x3 &matrix);

signals:

public slots:
};

#endif // RULESYSTEMINTERPRETER_H
