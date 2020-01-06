#ifndef CONTROL_OBJECT_H
#define CONTROL_OBJECT_H

#include "ConsoleEngine.h"

namespace ws
{
    class ControlObject
    {
        using vec2 = Vector2<int>;

    public:
        virtual void MoveRight(ConsoleEngine& game, vec2& drawingPos) = 0;
        virtual void MoveLeft(ConsoleEngine& game, vec2& drawingPos) = 0;

        virtual void TurnRight(ConsoleEngine& game, const vec2& drawingPos) = 0;
        virtual void TurnLeft(ConsoleEngine& game, const vec2& drawingPos) = 0;

        virtual void FallImmediate(ConsoleEngine& game, vec2& drawingPos) = 0;
    };
}

#endif // !CONTROL_OBJECT_H