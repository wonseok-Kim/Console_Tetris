#ifndef TETRIS_H
#define TETRIS_H

#include "Block.h"
#include "ConsoleEngine.h"

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
        { }

        void Update() override;

        void ExitGame();  

        bool IsStackable();

        void CheckLines();

        void BombOneLine(int y);

        bool IsFullLine(int y);

        void SetBlockStacked();

    private:
        Block mBlock;
        vec2 mDrawingPos;
        bool mbBlockIsCreated;
    };
}

#endif // !TETRIS_H