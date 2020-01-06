#pragma once

#include "ControlObject.h"

namespace ws
{
    using vec2 = Vector2<int>;

    class Command
    {
    public:
        virtual ~Command() { }
        
        virtual void Execute(ConsoleEngine& game, ControlObject& object, vec2& drawingPos) = 0;
    };

    class CommandMoveRight : public Command
    {
    public:
        void Execute(ConsoleEngine& game, ControlObject& object, vec2& drawingPos) override
        {
            object.MoveRight(game, drawingPos);
        }
    };

    class CommandMoveLeft : public Command
    {
    public:
        void Execute(ConsoleEngine& game, ControlObject& object, vec2& drawingPos) override
        {
            object.MoveLeft(game, drawingPos);
        }
    };

    class CommandMoveDown : public Command
    {
    public:
        void Execute(ConsoleEngine& game, ControlObject& object, vec2& drawingPos) override
        {
            object.FallImmediate(game, drawingPos);
        }
    };

    class CommandTurnRight : public Command
    {
    public:
        void Execute(ConsoleEngine& game, ControlObject& object, vec2& drawingPos) override
        {
            object.TurnRight(game, drawingPos);
        }
    };

    class CommandTurnLeft : public Command
    {
    public:
        void Execute(ConsoleEngine& game, ControlObject& object, vec2& drawingPos) override
        {
            object.TurnLeft(game, drawingPos);
        }
    };
}