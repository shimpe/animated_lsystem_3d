#ifndef RULE_H
#define RULE_H

#include <QString>

class Rule
{
public:
    Rule();
    Rule(const QString &LHS, const QString &rhs);

    QString LHS() const;
    void setLHS(const QString &LHS);

    QString RHS() const;
    void setRHS(const QString &RHS);

private:
    QString m_LHS;
    QString m_RHS;
};

#endif // RULE_H
