#include "operationrecognizer.h"
#include "rulesysteminterpreter.h"
#include "pipe3d.h"

#include <QMatrix3x3>
#include <cmath>

#ifndef M_PI
#include "pi.h"
#endif

RuleSystemInterpreter::RuleSystemInterpreter(QObject *parent)
    : QObject(parent)
    , m_cacheUpToDate(false)
    , m_turnAngleInDegree(0)
    , m_rollAngleInDegree(0)
    , m_pitchAngleInDegree(0)
    , m_turnAngleInRadians(0)
    , m_rollAngleInRadians(0)
    , m_pitchAngleInRadians(0)
    , m_xdir(1,0,0)
    , m_ydir(0,1,0)
    , m_zdir(0,0,1)
    , m_segmentLength(1.0)
    , m_segmentLengthContraction(1.0)
    , m_segmentThickness(0.1)
    , m_segmentThicknessContraction(1.0)
{}

void RuleSystemInterpreter::updateBasis(const QMatrix3x3 &matrix)
{
    // ugh...
    QMatrix3x3 basis;
    basis(0,0) = m_xdir.x();
    basis(1,0) = m_xdir.y();
    basis(2,0) = m_xdir.z();
    basis(0,1) = m_ydir.x();
    basis(1,1) = m_ydir.y();
    basis(2,1) = m_ydir.z();
    basis(0,2) = m_zdir.x();
    basis(1,2) = m_zdir.y();
    basis(2,2) = m_zdir.z();
    basis = basis * matrix;
    m_xdir.setX(basis(0,0));
    m_xdir.setY(basis(1,0));
    m_xdir.setZ(basis(2,0));
    m_ydir.setX(basis(0,1));
    m_ydir.setY(basis(1,1));
    m_ydir.setZ(basis(2,1));
    m_zdir.setX(basis(0,2));
    m_zdir.setY(basis(1,2));
    m_zdir.setZ(basis(2,2));
}

void RuleSystemInterpreter::recalculate()
{
    m_3dPipes.clear();

    OperationRecognizer r;
    for (auto &c : m_calculatedString) {
        Operations o = r.recognize(c);
        switch(o) {
        case CONSTANT:
            // skip
            break;
        case MOVE_FORWARD_PENUP:
            m_pos += m_xdir*m_segmentLength;
            break;
        case MOVE_FORWARD_PENDOWN:
        {
            QVector3D oldPos(m_pos);
            m_pos += m_xdir*m_segmentLength;
            m_3dPipes.append(new Pipe3D(oldPos, m_pos, m_segmentThickness));
            break;
        }
        case TURN_LEFT:
        {
            updateBasis(m_turnLeftRotationMatrix);
            break;
        }
        case TURN_RIGHT:
        {
            updateBasis(m_turnRightRotationMatrix);
            break;
        }
        case ROLL_LEFT:
        {
            updateBasis(m_rollLeftRotationMatrix);
            break;
        }
        case ROLL_RIGHT:
        {
            updateBasis(m_rollRightRotationMatrix);
            break;
        }
        case PITCH_UP:
        {
            updateBasis(m_pitchLeftRotationMatrix);
            break;
        }
        case PITCH_DOWN:
        {
            updateBasis(m_pitchRightRotationMatrix);
            break;
        }
        case REVERSE:
        {
            m_xdir.setX(-m_xdir.x());
            m_xdir.setY(-m_xdir.y());
            m_xdir.setZ(-m_xdir.z());
            m_ydir.setX(-m_ydir.x());
            m_ydir.setY(-m_ydir.y());
            m_ydir.setZ(-m_ydir.z());
            m_zdir.setX(-m_zdir.x());
            m_zdir.setY(-m_zdir.y());
            m_zdir.setZ(-m_zdir.z());
            break;
        }
        case INSERT_POINT:
        {
            // ??
            break;
        }
        case MULTIPLY_LENGTH:
        {
            m_segmentLength *= m_segmentLengthContraction;
            break;
        }
        case MULTIPLY_THICKNESS:
        {
            m_segmentThickness *= m_segmentThicknessContraction;
            break;
        }
        case START_BRANCH:
        {
            m_stackTurnAngle.push(m_turnAngleInDegree);
            m_stackRollAngle.push(m_rollAngleInDegree);
            m_stackPitchAngle.push(m_pitchAngleInDegree);
            m_stackSegmentLength.push(m_segmentLength);
            m_stackSegmentThickness.push(m_segmentThickness);
            m_stackxdir.push(m_xdir);
            m_stackydir.push(m_ydir);
            m_stackzdir.push(m_zdir);
            m_stackPos.push(m_pos);
            break;
        }
        case END_BRANCH:
        {
            if (!m_stackTurnAngle.empty())
            {
                setAnglesInDegree(m_stackTurnAngle.pop(), m_stackRollAngle.pop(), m_stackPitchAngle.pop());
                m_segmentLength = m_stackSegmentLength.pop();
                m_segmentThickness = m_stackSegmentThickness.pop();
                m_xdir = m_stackxdir.pop();
                m_ydir = m_stackydir.pop();
                m_zdir = m_stackzdir.pop();
                m_pos = m_stackPos.pop();
            }
            break;
        }
        }
    }
    m_cacheUpToDate = true;
}

void RuleSystemInterpreter::setCalculatedString(const QString &str)
{
    if (str != m_calculatedString)
    {
        m_calculatedString = str;
        m_cacheUpToDate = false;
        recalculate();
        setrefresh(true);
    }
}

void RuleSystemInterpreter::setSegmentLength(double len)
{
    if (m_segmentLength != len) {
        m_segmentLength = len;
        m_cacheUpToDate = false;
        recalculate();
        setrefresh(true);
    }
}

void RuleSystemInterpreter::setSegmentLengthContraction(double lenContraction)
{
    if (m_segmentLengthContraction != lenContraction) {
        m_segmentLengthContraction = lenContraction;
        m_cacheUpToDate = false;
        recalculate();
        setrefresh(true);
    }
}

void RuleSystemInterpreter::setSegmentThickness(double thickness)
{
    if (m_segmentThickness != thickness)
    {
        m_segmentThickness = thickness;
        m_cacheUpToDate = false;
        recalculate();
        setrefresh(true);
    }
}

void RuleSystemInterpreter::setSegmentThicknessContraction(double thicknessContraction)
{
    if (m_segmentThicknessContraction != thicknessContraction)
    {
        m_segmentThicknessContraction = thicknessContraction;
        m_cacheUpToDate = false;
        recalculate();
        setrefresh(true);
    }
}

double RuleSystemInterpreter::segmentLength() const
{
    return m_segmentLength;
}

double RuleSystemInterpreter::segmentLengthContraction() const
{
    return m_segmentLengthContraction;
}

double RuleSystemInterpreter::segmentThickness() const
{
    return m_segmentThickness;
}

double RuleSystemInterpreter::segmentThicknessContraction() const
{
    return m_segmentThicknessContraction;
}

int RuleSystemInterpreter::noOfPipes() const
{
    return m_3dPipes.size();
}

QVector3D RuleSystemInterpreter::getFrom(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->from();

    return QVector3D();
}

QVector3D RuleSystemInterpreter::getTo(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->to();

    return QVector3D();
}

double RuleSystemInterpreter::w(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->w();
    return 0;
}

double RuleSystemInterpreter::h(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->h();
    return 0;
}

double RuleSystemInterpreter::d(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->d();
    return 0;}

double RuleSystemInterpreter::l(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->l();
    return 0;
}

double RuleSystemInterpreter::lxz(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->lxz();
    return 0;
}

double RuleSystemInterpreter::tx(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->tx();
    return 0;
}

double RuleSystemInterpreter::ty(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->ty();
    return 0;
}

double RuleSystemInterpreter::tz(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->tz();
    return 0;
}

double RuleSystemInterpreter::anglex(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->anglex();
    return 0;
}

double RuleSystemInterpreter::angley(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->angley();
    return 0;
}

double RuleSystemInterpreter::thickness(int pipeidx) const
{
    if (pipeidx < m_3dPipes.size())
        return m_3dPipes.at(pipeidx)->thickness();
    return 0;
}

void RuleSystemInterpreter::setAnglesInDegree(double turnAngle_deg, double rollAngle_deg, double pitchAngle_deg)
{
    if (turnAngle_deg != m_turnAngleInDegree ||
            rollAngle_deg != m_rollAngleInDegree ||
            pitchAngle_deg != m_pitchAngleInDegree)
    {
        m_turnAngleInDegree = turnAngle_deg;
        m_turnAngleInRadians = turnAngle_deg*M_PI/180;
        m_turnLeftRotationMatrix.setToIdentity();
        m_turnLeftRotationMatrix(0,0) = cos(m_turnAngleInRadians);
        m_turnLeftRotationMatrix(0,1) = sin(m_turnAngleInRadians);
        m_turnLeftRotationMatrix(1,0) = -m_turnLeftRotationMatrix(0,1);
        m_turnLeftRotationMatrix(1,1) = m_turnLeftRotationMatrix(0,0);
        m_turnRightRotationMatrix.setToIdentity();
        m_turnRightRotationMatrix(0,0) = cos(-m_turnAngleInRadians);
        m_turnRightRotationMatrix(0,1) = sin(-m_turnAngleInRadians);
        m_turnRightRotationMatrix(1,0) = -m_turnRightRotationMatrix(0,1);
        m_turnRightRotationMatrix(1,1) = m_turnRightRotationMatrix(0,0);

        m_rollAngleInDegree = rollAngle_deg;
        m_rollAngleInRadians = rollAngle_deg*M_PI/180;
        m_rollLeftRotationMatrix.setToIdentity();
        m_rollLeftRotationMatrix(0,0) = cos(m_rollAngleInRadians);
        m_rollLeftRotationMatrix(2,0) = sin(m_rollAngleInRadians);
        m_rollLeftRotationMatrix(0,2) = -m_rollLeftRotationMatrix(2,0);
        m_rollLeftRotationMatrix(2,2) = m_rollLeftRotationMatrix(0,0);
        m_rollRightRotationMatrix.setToIdentity();
        m_rollRightRotationMatrix(0,0) = cos(-m_rollAngleInRadians);
        m_rollRightRotationMatrix(2,0) = sin(-m_rollAngleInRadians);
        m_rollRightRotationMatrix(0,2) = -m_rollRightRotationMatrix(2,0);
        m_rollRightRotationMatrix(2,2) = m_rollRightRotationMatrix(0,0);

        m_pitchAngleInDegree =  pitchAngle_deg;
        m_pitchAngleInRadians = pitchAngle_deg*M_PI/180;
        m_pitchLeftRotationMatrix.setToIdentity();
        m_pitchLeftRotationMatrix(1,1) = cos(m_pitchAngleInRadians);
        m_pitchLeftRotationMatrix(2,1) = sin(m_pitchAngleInRadians);
        m_pitchLeftRotationMatrix(1,2) = -m_pitchLeftRotationMatrix(2,1);
        m_pitchLeftRotationMatrix(2,2) = m_pitchLeftRotationMatrix(1,1);
        m_pitchRightRotationMatrix.setToIdentity();
        m_pitchRightRotationMatrix(1,1) = cos(-m_pitchAngleInRadians);
        m_pitchRightRotationMatrix(2,1) = sin(-m_pitchAngleInRadians);
        m_pitchRightRotationMatrix(1,2) = -m_pitchRightRotationMatrix(2,1);
        m_pitchRightRotationMatrix(2,2) = m_pitchRightRotationMatrix(1,1);
        m_cacheUpToDate = false;
        recalculate();
        setrefresh(true);
    }
}

bool RuleSystemInterpreter::refresh() const
{
    return true;
}

void RuleSystemInterpreter::setrefresh(bool parameter)
{
    if (parameter)
        emit refreshChanged();
}
