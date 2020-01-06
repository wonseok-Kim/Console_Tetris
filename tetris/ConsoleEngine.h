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
        block,  // moving down block
        stack,  // fixed block 
        boundary, 
        effect  // when line is full, show effect
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

        void Run(); // 게임 메인 루프가 있는 함수

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
        // 왼쪽 아래를 (0,0)으로 하고 싶어서 화면 출력할 때는 윈도우 좌표계?로 변환해줌
        // 2바이트 문자를 사용하고 있기 때문에 x좌표를 2배로 곱해주는 기능도 있음
        void moveCursorTo(short x, short y);

        // 경계선을 생각안하고 코딩하기 위해서 엔진단에서 경계선을 더해줌
        vec2 convertPosition(int x, int y) { return vec2{ x + 1, y + 1 }; }
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
