#ifndef CONSOLE_ENGINE_H
#define CONSOLE_ENGINE_H

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
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
        effect
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

        void Draw(int x, int y, Shape shape);
        void Draw(const vec2& pos, Shape shape);

        bool IsKeyPressing();
        bool IsKeyPressed(int flag) { return (flag == mInputKey); }

        int GetWidth() const { return mWidth -2; }     // minus boundary
        int GetHeight() const { return mHeight - 2; }  // minus boundary

        Shape GetShape(int x, int y);
        Shape GetShape(const vec2& pos);

    private:
        void moveCursorTo(short x, short y);

        vec2 convertPosition(int x, int y) { return vec2{ x + 1, y + 1}; }
        vec2 convertPosition(const vec2& pos) { return vec2{ pos.x + 1, pos.y + 1 }; }

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
