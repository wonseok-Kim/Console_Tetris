#include "Tetris.h"

namespace ws
{
    void Tetris::Update()
    {
        if (!mbBlockIsCreated)
        {
            mBlock.Select();
            mDrawingPos = vec2{ GetWidth() / 2 - 2, GetHeight() - 1 };
            mbBlockIsCreated = true;
        }

        if (mBlock.CheckDrawingPossible(*this, mDrawingPos))
            mBlock.Draw(*this, mDrawingPos);
        else
            ExitGame();
        
        if (IsKeyPressing())
        {
            inputHandler.Handle(*this, mBlock, mDrawingPos);

            if (mBlock.CheckDrawingPossible(*this, mDrawingPos))
                mBlock.Draw(*this, mDrawingPos);
            else
                ExitGame();
        }

        CheckLines();
        
        if (IsStackable())
        {
            mbBlockIsCreated = false;
            mBlock.SetStackFlag(true);
            SetBlockStacked();
        }
        else
        {
            --mDrawingPos.y; // move down
        }
    }
    
    void Tetris::ExitGame()
    {
        std::system("cls");
        std::cout << "Game Over\n";
        std::exit(EXIT_SUCCESS);
    }
    
    bool Tetris::IsStackable()
    {
        auto belowPos{ mBlock.GetBelowPos() };

        for (unsigned i{ 0 }; i < belowPos.size(); ++i)
        {
            if (auto shape{ GetShape(belowPos[i]) };
                shape == Shape::stack || shape == Shape::boundary)
            {
                return true;
            }
        }

        return false;
    }

    void Tetris::SetEffectLine(int line)
    {
        for (int x{ 0 }; x < GetWidth(); ++x)
        {
            SetScreenBuffer(x, line, Shape::effect);
        }
    }

    void Tetris::CheckLines()
    {
        for (int y{ 0 }; y < GetHeight() - 2; ++y)
        {
            if (IsFullLine(y))
            {
                SetEffectLine(y);
                OutputScreen();
                Sleep(100);
                EraseLine(y);
            }
        }
    }

    void Tetris::EraseLine(int line)
    {
        for (int row{ line }; row < GetHeight() - 1; ++row)
        {
            for (int col{ 0 }; col < GetWidth(); ++col)
            {
                SetScreenBuffer(col, row, GetShape(col, row + 1));
                SetScreenBuffer(col, row + 1, Shape::blank);
            }
        }
    }

    bool Tetris::IsFullLine(int y)
    {
        vec2 pos{ 0, y };
        for (; pos.x < GetWidth(); ++pos.x)
        {
            if (GetShape(pos) != Shape::stack)
                return false;
        }
        return true;
    }
    
    void Tetris::SetBlockStacked()
    {
        for (const auto& pos : mBlock.GetBlockPos())
        {
            SetScreenBuffer(pos, Shape::stack);
        }
    }
}