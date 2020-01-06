#ifndef BLOCK_H
#define BLOCK_H

#include <array>

#include "ConsoleEngine.h"
#include "ControlObject.h"

namespace ws
{
    class Block : public ControlObject
    {
    public:
        using vec2 = Vector2<int>;

        Block()
        {
            mBelowPos.reserve(4);
            mBlockPos.reserve(4);
        }

        void Select();

        bool CheckDrawingPossible(ConsoleEngine& game, const vec2& drawingPos);

        void Draw(ConsoleEngine& game, const vec2& drawingPos);    

        void MoveRight(ConsoleEngine& game, vec2& drawingPos) override;
        void MoveLeft(ConsoleEngine& game, vec2& drawingPos) override;

        void TurnRight(ConsoleEngine& game, const vec2& drawingPos) override;
        void TurnLeft(ConsoleEngine& game, const vec2& drawingPos) override;

        void FallImmediate(ConsoleEngine& game, vec2& drawingPos) override;

        auto GetBelowPos() const -> const std::vector<vec2>& { return mBelowPos; }
        auto GetBlockPos() const -> const std::vector<vec2>& { return mBlockPos; }

        void SetStackFlag(bool flag) { mbStacked = flag; }

    private:
        bool checkBitmask(int x, int y);

        void erasePreviousBlock(ConsoleEngine& game);

        bool isPossibleTurnRight(ConsoleEngine& game, const vec2& drawingPos);
        bool isPossibleTurnLeft(ConsoleEngine& game, const vec2& drawingPos);

        void rotateRight();
        void rotateLeft();

    private:
        std::array<std::array<int, 4>, 7> mBlocks{
           {{0x4640, 0x0E40, 0x4C40, 0x4E00},  // 'T' Block
           {0x8C40, 0x6C00, 0x8C40, 0x6C00},   // 'S' Block
           {0x4C80, 0xC600, 0x4C80, 0xC600},   // 'Z' Block
           {0x4444, 0x0F00, 0x4444, 0x0F00},   // 'I' Block
           {0x44C0, 0x8E00, 0xC880, 0xE200},   // 'J' Block
           {0x88C0, 0xE800, 0xC440, 0x2E00},   // 'L' Block
           {0xCC00, 0xCC00, 0xCC00, 0xCC00} }  // 'O' Block
        };

        std::vector<vec2> mBelowPos;
        std::vector<vec2> mBlockPos;

        int mCurrentIndex{ 0 };
        int mNextIndex{ -1 };
        int mRotateIndex{ 0 };

        bool mbStacked{ false };
    };
}

#endif BLOCK_H