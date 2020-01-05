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

        void CheckStack()
        {
            for (int y{ 0 }; y < GetHeight() - 2; ++y)
            {
                if (IsFull(y))
                {
                    BombOneLine(y);
                }
            }
        }

        void BombOneLine(int y)
        {
            for (int row{ y }; row < GetHeight() - 1; ++row)
            {
                for (int col{ 0 }; col < GetWidth() - 1; ++col)
                {
                    Draw(col, row, GetShape(col, row + 1));
                    Draw(col, row + 1, Shape::blank);
                }
            }
        }

        bool IsFull(int y)
        {
            vec2 pos{ 0, y };
            for (; pos.x < GetWidth(); ++pos.x)
            {
                if (GetShape(pos) != Shape::stack)
                    return false;
            }
            return true;
        }

        void SetBlockStacked();

    private:
        Block mBlock;
        vec2 mDrawingPos;
        bool mbBlockIsCreated;
    };
}

#endif // !TETRIS_H