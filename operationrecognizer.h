#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QSet>
#include <QChar>

enum Operations {
    CONSTANT,             // symbol that is to be ignored (placeholder for building up rules)
    MOVE_FORWARD_PENDOWN, // move forward at distance L(Step Length) and draw a line
    MOVE_FORWARD_PENUP,   // move forward at distance L(Step Length) without drawing a line
    TURN_LEFT,            // + turn left A(Default Angle) degrees
    TURN_RIGHT,           // – turn right A(Default Angle) degrees
    ROLL_LEFT,            // \ roll left A(Default Angle) degrees
    ROLL_RIGHT,           // / roll right A(Default Angle) degrees
    PITCH_UP,             // ^ pitch up A(Default Angle) degrees
    PITCH_DOWN,           // & pitch down A(Default Angle) degrees
    REVERSE,              // | turn around 180 degrees
    INSERT_POINT,         // J insert point at this position
    MULTIPLY_LENGTH,      // " multiply current length by dL(Length Scale)
    MULTIPLY_THICKNESS,   // ! multiply current thickness by dT(Thickness Scale)
    START_BRANCH,         // [ start a branch(push turtle state)
    END_BRANCH,           // ] end a branch(pop turtle state)
};

class OperationRecognizer
{
public:
    OperationRecognizer() = default;

    Operations recognize(const QChar &ch);

    void registerConstant(const QChar &ch);

private:
    bool isConstant(const QChar &ch) const;
    bool isPenUp(const QChar &ch) const;

private:
    QSet<QChar> m_Constants;
};

#endif // OPERATIONS_H
