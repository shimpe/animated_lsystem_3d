#include "pipe3d.h"
#include <cmath>

#ifndef M_PI
#include "pi.h"
#endif

double Pipe3D::w() const
{
    return to().x() - from().x();
}

double Pipe3D::h() const
{
    return to().y() - from().y();
}

double Pipe3D::d() const
{
    return to().z() - from().z();
}

double Pipe3D::l() const
{
    double W = w();
    double H = h();
    double D = d();
    return sqrt(W*W+H*H+D*D);
}

double Pipe3D::lxz() const
{
    double W = w();
    double D = d();
    return sqrt(W*W + D*D);
}

double Pipe3D::tx() const
{
    return from().x() + w()/2.0;
}

double Pipe3D::ty() const
{
    return from().y() + h()/2.0;
}

double Pipe3D::tz() const
{
    return from().z() + d()/2.0;
}

double Pipe3D::anglex() const
{
    double L = l();
    return L < 1e-10 ? 0 : acos(h()/L)*180/M_PI;
}

double Pipe3D::angley() const
{
    double LXZ = lxz();
    return LXZ < 1e-10 ? 0 : acos(d()/LXZ)*180/M_PI;
}

double Pipe3D::thickness() const
{
    return m_thickness;
}

const QVector3D &Pipe3D::from() const
{
    return m_from;
}

const QVector3D &Pipe3D::to() const
{
    return m_to;
}

double Pipe3D::jointExpansion() const
{
    return m_jointExpansion;
}
