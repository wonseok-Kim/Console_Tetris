#include "Block.h"

namespace ws
{
    void Block::Select()
    {
        if (mNextIndex == -1)
        {
            mCurrentIndex = 3; //rand() % 7;  TODEBUG
            mNextIndex = 6;
            return;
        }

        mCurrentIndex = mNextIndex;
        mNextIndex = rand() % 7;
    }

    bool Block::Draw(ConsoleEngine& game, vec2& drawingPos)
    {
        mBelowPos.clear();
        if (mBlockPos.size() > 0)
        {
            if (!mbStacked)
                erasePreviousBlock(game);
            
            mbStacked = false;
            mBlockPos.clear();
        }

        for (int y{ 0 }; y < 4; ++y)
        {
            for (int x{ 0 }; x < 4; ++x)
            {
                if (checkBitmask(x, y))
                {
                    vec2 pos{ drawingPos.x + x, drawingPos.y - y };

                    if (game.GetShape(pos) == Shape::stack)
                        return false;
                    
                    game.Draw(pos, Shape::block);

                    mBlockPos.push_back(pos);
                    mBelowPos.push_back({ pos.x, pos.y - 1 });
                }
            }
        }

    sorry:
        for (int i{ 0 }; i < mBelowPos.size(); ++i)
        {
            if (game.GetShape(mBelowPos[i]) == Shape::block)
            {
                mBelowPos.erase(mBelowPos.begin() + i);
                goto sorry;
            }
        }

        return true;
    }

    bool Block::IsPossibleTurnRight(ConsoleEngine& game, vec2& drawingPos)
    {
        TurnRight();

        for (int y{ 0 }; y < 4; ++y)
        {
            for (int x{ 0 }; x < 4; ++x)
            {
                if (checkBitmask(x, y))
                {
                    try
                    {
                        vec2 pos{ drawingPos.x + x, drawingPos.y - y };

                        if (auto temp{ game.GetShape(pos) };
                            temp == Shape::boundary || temp == Shape::stack)
                        {
                            TurnLeft();
                            return false;
                        }
                    }
                    catch (...)
                    {
                        TurnLeft();
                        return false;
                    }
                }
            }
        }
        TurnLeft();
        return true;
    }

    bool Block::IsPossibleTurnLeft(ConsoleEngine& game, vec2& drawingPos)
    {
        TurnLeft();

        for (int y{ 0 }; y < 4; ++y)
        {
            for (int x{ 0 }; x < 4; ++x)
            {
                try
                {
                    if (checkBitmask(x, y))
                    {
                        vec2 pos{ drawingPos.x + x, drawingPos.y - y };

                        if (auto temp{ game.GetShape(pos) };
                            temp == Shape::boundary || temp == Shape::stack)
                        {
                            TurnRight();
                            return false;
                        }
                    }
                }
                catch (...)
                {
                    TurnRight();
                    return false;
                }
            }
        }
        TurnRight();
        return true;
    }

    void Block::TurnRight()
    {
        if (mRotateIndex >= 0 && mRotateIndex < 3)
            ++mRotateIndex;
        else if (mRotateIndex == 3)
            mRotateIndex = 0;
    }

    void Block::TurnLeft()
    {
        if (mRotateIndex > 0 && mRotateIndex <= 3)
            --mRotateIndex;
        else if (mRotateIndex == 0)
            mRotateIndex = 3;
    }
    
    bool Block::checkBitmask(int x, int y)
    {
        assert(x < 4 && x >= 0);
        assert(y < 4 && y >= 0);
        int bit = mBlocks[mCurrentIndex][mRotateIndex];

        return (bit >> (y * 4 + x)) & 1;
    }

    void Block::erasePreviousBlock(ConsoleEngine& game)
    {
        for (unsigned i{ 0 }; i < 4; ++i)
        {
            game.Draw(mBlockPos[i].x, mBlockPos[i].y, Shape::blank);
        }
    }
}