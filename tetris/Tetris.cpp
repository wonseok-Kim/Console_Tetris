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
        if (mBlock.Draw(*this, mDrawingPos) == false) { ExitGame(); }

        OutputScreen();

        if (IsKeyPressing())
        {
            bool bMovePossible{ true };
            if (IsKeyPressed(KEY_LEFT))
            {
                for (const auto& pos : mBlock.GetBlockPos())
                {
                    if (pos.x == 0)
                        bMovePossible = false;

                    if (GetShape(pos.x - 1, pos.y) == Shape::stack)
                        bMovePossible = false;
                }
                if (bMovePossible)
                    --mDrawingPos.x;
            }
            else if (IsKeyPressed(KEY_RIGHT))
            {
                for (const auto& pos : mBlock.GetBlockPos())
                {
                    if (pos.x == GetWidth() - 1)
                        bMovePossible = false;

                    if (GetShape(pos.x + 1, pos.y) == Shape::stack)
                        bMovePossible = false;
                }
                if (bMovePossible)
                    ++mDrawingPos.x;
            }
            else if (IsKeyPressed(KEY_Z))
            {
                if (mBlock.IsPossibleTurnLeft(*this, mDrawingPos))
                {
                    mBlock.TurnLeft();
                }
            }
            else if (IsKeyPressed(KEY_X))
            {
                if (mBlock.IsPossibleTurnRight(*this, mDrawingPos))
                {
                    mBlock.TurnRight();
                }
            }

            if (mBlock.Draw(*this, mDrawingPos) == false) { ExitGame(); }
            OutputScreen();
        }

        CheckStack();
        
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
    
    void Tetris::SetBlockStacked()
    {
        for (const auto& pos : mBlock.GetBlockPos())
        {
            Draw(pos, Shape::stack);
        }
    }
}