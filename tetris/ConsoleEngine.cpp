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
                    case Shape::block: std::cout << "бс"; break;
                    case Shape::stack: std::cout << "бс"; break;
                    case Shape::boundary: std::cout << "бс"; break;
                    default: assert(0);

                    }
                }
            }
        }
        Sleep(33);
    }

    void ConsoleEngine::init()
    {
        std::srand(static_cast<unsigned>(std::time(0)));
        std::rand();  // dummy

        CONSOLE_CURSOR_INFO cursorInfo = { 0, };
        cursorInfo.dwSize = 1;
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

        mBackBuffer.resize(mHeight);
        for (auto& row : mBackBuffer)
        {
            row.resize(mWidth);
        }

        mFrontBuffer = mBackBuffer;

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