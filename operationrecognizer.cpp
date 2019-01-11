#include "operationrecognizer.h"

Operations OperationRecognizer::recognize(const QChar &ch)
{
    if (isConstant(ch))
    {
        return CONSTANT;
    }

    switch(ch.unicode()) {
    case '+':
        return TURN_LEFT;
    case '-':
        return TURN_RIGHT;
    case '\\':
        return ROLL_LEFT;
    case'/' :
        return ROLL_RIGHT;
    case '^':
        return PITCH_UP;
    case '&':
        return PITCH_DOWN;
    case '|':
        return REVERSE;
    case 'J':
        return INSERT_POINT;
    case '"':
        return MULTIPLY_LENGTH;
    case '!':
        return MULTIPLY_THICKNESS;
    case '[':
        return START_BRANCH;
    case ']':
        return END_BRANCH;
    case 'C':
        return COLOR_CHANGE;
    default:
        if (isPenUp(ch))
        {
            return MOVE_FORWARD_PENUP;
        }
        else
        {
            return MOVE_FORWARD_PENDOWN;
        }
    }
}

void OperationRecognizer::registerConstant(const QChar &ch)
{
    m_Constants.insert(ch);
}

bool OperationRecognizer::isConstant(const QChar &ch) const
{
    return m_Constants.contains(ch);
}

bool OperationRecognizer::isPenUp(const QChar &ch) const
{
    return ch.isLower();
}
