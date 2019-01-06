#include "rule.h"
#include <string>

Rule::Rule()
{
}

Rule::Rule(const QString &LHS, const QString &RHS)
    : m_LHS(LHS)
    , m_RHS(RHS)
{
}

QString Rule::LHS() const
{
    return m_LHS;
}

void Rule::setLHS(const QString &LHS)
{
    m_LHS = LHS;
}

QString Rule::RHS() const
{
    return m_RHS;
}

void Rule::setRHS(const QString &RHS)
{
    m_RHS = RHS;
}
