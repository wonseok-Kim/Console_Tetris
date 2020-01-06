#include "Block.h"

namespace ws
{
    void Block::Select()
    {
        if (mNextIndex == -1)
        {
            mCurrentIndex = rand() % 7;  
            mNextIndex = rand() % 7;
            return;
        }

        mCurrentIndex = mNextIndex;
        mNextIndex = rand() % 7;
    }

    void Block::Draw(ConsoleEngine& game, const vec2& drawingPos)
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

                    game.SetScreenBuffer(pos, Shape::block);

                    mBlockPos.push_back(pos);
                    mBelowPos.push_back({ pos.x, pos.y - 1 });
                }
            }
        }

    loop_again: // Because index is modified when erase, begin loop again
        for (int i{ 0 }; i < mBelowPos.size(); ++i)
        {
            if (game.GetShape(mBelowPos[i]) == Shape::block)
            {
                mBelowPos.erase(mBelowPos.begin() + i);
                goto loop_again;
            }
        }

        game.OutputScreen();
    }

    void Block::MoveRight(ConsoleEngine& game, vec2& drawingPos)
    {
        bool bMovePossible{ true };

        for (const auto& pos : mBlockPos)
        {
            if (pos.x == game.GetWidth() - 1)
                bMovePossible = false;

            if (auto temp{ game.GetShape(pos.x + 1, pos.y) };
                temp == Shape::stack)
                bMovePossible = false;
        }
        if (bMovePossible)
            ++drawingPos.x;
    }

    void Block::MoveLeft(ConsoleEngine& game, vec2& drawingPos)
    {
        bool bMovePossible{ true };

        for (const auto& pos : mBlockPos)
        {
            if (pos.x == 0)
                bMovePossible = false;

            if (auto temp{ game.GetShape(pos.x - 1, pos.y) };
                temp == Shape::stack)
                bMovePossible = false;
        }
        if (bMovePossible)
            --drawingPos.x;
    }

    bool Block::CheckDrawingPossible(ConsoleEngine& game, const vec2& drawingPos)
    {
        for (int y{ 0 }; y < 4; ++y)
        {
            for (int x{ 0 }; x < 4; ++x)
            {
                if (checkBitmask(x, y))
                {
                    try  
                    {
                        vec2 pos{ drawingPos.x + x, drawingPos.y - y };

                        // When invalid pos passed to GetShape, throw std::out_of_range
                        if (auto temp{ game.GetShape(pos) }; 
                            temp == Shape::boundary || temp == Shape::stack)
                            return false;
                    }
                    catch (const std::out_of_range&)
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void Block::TurnRight(ConsoleEngine& game, const vec2& drawingPos)
    {
        if (isPossibleTurnRight(game, drawingPos))
            rotateRight();
    }

    void Block::TurnLeft(ConsoleEngine& game, const vec2& drawingPos)
    {
        if (isPossibleTurnLeft(game, drawingPos))
            rotateLeft();
    }

    void Block::FallImmediate(ConsoleEngine& game, vec2& drawingPos)
    {
        vec2 tempPos{ drawingPos.x, 3 };

        for (; tempPos.y < game.GetWidth(); ++tempPos.y)
        {
            if (CheckDrawingPossible(game, tempPos))
            {
                drawingPos = tempPos;
                return;
            }
        }
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
            game.SetScreenBuffer(mBlockPos[i].x, mBlockPos[i].y, Shape::blank);
        }
    }

    bool Block::isPossibleTurnRight(ConsoleEngine& game, const vec2& drawingPos)
    {
        bool bPossibleTurn{ false };
        rotateRight();

        if (CheckDrawingPossible(game, drawingPos))
            bPossibleTurn = true;

        rotateLeft();
        return bPossibleTurn;
    }

    bool Block::isPossibleTurnLeft(ConsoleEngine& game, const vec2& drawingPos)
    {
        bool bPossibleTurn{ false };
        rotateLeft();

        if (CheckDrawingPossible(game, drawingPos))
            bPossibleTurn = true;

        rotateRight();
        return bPossibleTurn;
    }
    
    void Block::rotateRight()
    {
        if (mRotateIndex >= 0 && mRotateIndex < 3)
            ++mRotateIndex;
        else if (mRotateIndex == 3)
            mRotateIndex = 0;
    }
    
    void Block::rotateLeft()
    {
        if (mRotateIndex > 0 && mRotateIndex <= 3)
            --mRotateIndex;
        else if (mRotateIndex == 0)
            mRotateIndex = 3;
    }
}