#ifndef TETRIS_H
#define TETRIS_H

#include "Block.h"
#include "ConsoleEngine.h"
#include "InputHandler.h"

namespace ws
{
    class Tetris : public ConsoleEngine
    {
    public:
        Tetris(int width = 15, int height = 30)
            : ConsoleEngine{ width, height }
            , mBlock{}
            , mDrawingPos{}
            , mbBlockIsCreated{ false }
        {
            inputHandler.SetCommand(KEY_RIGHT) = new CommandMoveRight{};
            inputHandler.SetCommand(KEY_LEFT)  = new CommandMoveLeft{};
            inputHandler.SetCommand(KEY_DOWN)  = new CommandMoveDown{};
            inputHandler.SetCommand(KEY_Z)     = new CommandTurnLeft{};
            inputHandler.SetCommand(KEY_X)     = new CommandTurnRight{};
        }

        void Update() override; // Game main logic

        void ExitGame();  

        bool IsStackable();

        void SetEffectLine(int line);

        void CheckLines();

        void EraseLine(int line);

        bool IsFullLine(int y);

        void SetBlockStacked();

    private:
        InputHandler inputHandler;
        Block mBlock;
        vec2 mDrawingPos;
        bool mbBlockIsCreated;
    };
}

#endif // !TETRIS_H