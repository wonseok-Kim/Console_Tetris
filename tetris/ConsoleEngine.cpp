#include "ConsoleEngine.h"

namespace ws
{
    void ConsoleEngine::Run()
    {
        while (true)
        {
            OutputScreen();

            Update();
        }
    }

    void ConsoleEngine::OutputScreen()
    {
        for (int y{ 0 }; y < mHeight; ++y)
        {
            for (int x{ 0 }; x < mWidth; ++x)
            {
                moveCursorTo(x, y);

                if (mFrontBuffer[y][x] != mBackBuffer[y][x])
                {
                    mFrontBuffer[y][x] = mBackBuffer[y][x];
                    switch (mFrontBuffer[y][x])
                    {
                    case Shape::blank: std::cout << "  "; break;
                    case Shape::block: std::cout << "■"; break;
                    case Shape::stack: std::cout << "■"; break;
                    case Shape::effect: std::cout << "♨"; break;
                    case Shape::boundary: std::cout << "■"; break;
                    default: assert(0);

                    }
                }
            }
        }
        Sleep(33);
    }

    void ConsoleEngine::Draw(int x, int y, Shape shape)
    {
        vec2 temp{ convertPosition(x, y) };
        mBackBuffer[temp.y][temp.x] = shape;
    }

    void ConsoleEngine::Draw(const vec2& pos, Shape shape)
    {
        vec2 temp{ convertPosition(pos) };
        mBackBuffer[temp.y][temp.x] = shape;
    }

    bool ConsoleEngine::IsKeyPressing()
    {
        bool bPressing{ (_kbhit() != 0) ? true : false };

        if (bPressing)
        {
            mInputKey = _getch();

            if (mInputKey == KEY_ARROWS_FLAG)
                mInputKey = _getch();
        }

        return bPressing;
    }

    Shape ConsoleEngine::GetShape(int x, int y)
    {
        vec2 temp{ convertPosition(x, y) };
        return mBackBuffer.at(temp.y).at(temp.x);
    }

    Shape ConsoleEngine::GetShape(const vec2& pos)
    {
        vec2 temp{ convertPosition(pos) };
        return mBackBuffer.at(temp.y).at(temp.x);
    }

    void ConsoleEngine::moveCursorTo(short x, short y)
    {
        COORD cursorPos = { static_cast<short>(x * 2), static_cast<short>(mHeight - y - 1) };

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
    }

    
    void ConsoleEngine::init()
    {
        std::srand(static_cast<unsigned>(std::time(0)));
        std::rand();  // learncpp.com에서 vs는 첫 rand()값을 버려야 된다네요.

        // make cursor nonvisible
        CONSOLE_CURSOR_INFO cursorInfo = { 0, };
        cursorInfo.dwSize = 1;
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

        mBackBuffer.resize(mHeight);
        for (auto& col : mBackBuffer)
            col.resize(mWidth);

        mFrontBuffer.resize(mHeight);
        for (auto& col : mFrontBuffer)
            col.resize(mHeight);
             

        for (int y{ 0 }; y < mHeight; ++y)
        {
            for (int x{ 0 }; x < mWidth; ++x)
            {
                if (x == 0 || y == 0 || x == mWidth - 1 || y == mHeight - 1)
                {
                    mBackBuffer[y][x] = Shape::boundary;
                }
                else
                {
                    mBackBuffer[y][x] = Shape::blank;
                }
            }
        }
    }
}