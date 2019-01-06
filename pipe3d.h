#ifndef ROD_H
#define ROD_H

#include <QObject>
#include <QVector3D>

class Pipe3D : public QObject
{
    Q_OBJECT

public:
    explicit Pipe3D(QObject *parent = nullptr)
        : QObject(parent)
        , m_thickness(0.1)
    {
    }
    explicit Pipe3D(const QVector3D &from, const QVector3D &to, double thickness, QObject *parent = nullptr)
        : QObject (parent)
        , m_from(from)
        , m_to(to)
        , m_thickness(thickness)
    {
    }
    double w() const;
    double h() const;
    double d() const;
    double l() const;
    double lxz() const;
    double tx() const;
    double ty() const;
    double tz() const;
    double anglex() const;
    double angley() const;
    double thickness() const;
    const QVector3D &from() const;
    const QVector3D &to() const;

signals:

public slots:

private:
    QVector3D m_from;
    QVector3D m_to;
    double m_thickness;
};

#endif // ROD_H
