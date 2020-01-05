#ifndef CONSOLE_ENGINE_H
#define CONSOLE_ENGINE_H

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include <conio.h>
#include <Windows.h>

#include "KeyMacro.h"
#include "Vector2D.h"

namespace ws
{
    enum class Shape : unsigned char
    {
        blank,
        block,
        stack,
        boundary,
    };

    class ConsoleEngine
    {
    public:
        using vec2 = Vector2<int>;

        ConsoleEngine(const int& width, const int& height)
            : mWidth{ width + 2 }, mHeight{ height + 2 } // add boundary
        {
            init();
        }

        void Run();

        virtual void Update() = 0;

        void OutputScreen();

        void Draw(int x, int y, Shape shape)
        {
            vec2 temp{ convertPosition(x, y) };

            mBackBuffer[temp.y][temp.x] = shape;
        }

        void Draw(const vec2& pos, Shape shape)
        {
            vec2 temp{ convertPosition(pos) };

            mBackBuffer[temp.y][temp.x] = shape;
        }

        bool IsKeyPressing()
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

        bool IsKeyPressed(int flag)
        {
            return (flag == mInputKey);
        }

        int GetWidth() const { return mWidth -2; }     // minus boundary
        int GetHeight() const { return mHeight - 2; }  // minus boundary
        Shape GetShape(int x, int y)
        {
            if (x < -1 || x > GetWidth() ||
                y < -1 || y > GetHeight() - 1)
            {
                throw - 1;
            }
            vec2 temp{ convertPosition(x, y) };
            return mBackBuffer[temp.y][temp.x];
        }
        Shape GetShape(const vec2& pos)
        {
            if (pos.x < -1 || pos.x > GetWidth() ||
                pos.y < -1 || pos.y > GetHeight() - 1)
            {
                throw - 1;
            }
            vec2 temp{ convertPosition(pos) };
            return mBackBuffer[temp.y][temp.x];
        }

    private:
        void moveCursorTo(short x, short y)
        {
            COORD cursorPos = { static_cast<short>(x * 2), static_cast<short>(mHeight - y - 1) };

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
        }

        vec2 convertPosition(int x, int y)
        {
            return vec2{ x + 1, y + 1};
        }

        vec2 convertPosition(const vec2& pos)
        {
            return vec2{ pos.x + 1, pos.y + 1 };
        }

        void init();

    private:
        int mWidth;
        int mHeight;
        std::vector<std::vector<Shape>> mFrontBuffer;
        std::vector<std::vector<Shape>> mBackBuffer;
        int mInputKey;
    };
}

#endif // !CONSOLE_ENGINE_H
