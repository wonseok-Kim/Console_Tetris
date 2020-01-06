#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <map>

#include "Command.h"

namespace ws
{
    class InputHandler
    {
    public:
        ~InputHandler ()
        {
            for (auto& m : keyMap)
            {
                delete m.second;
            }
        }

        void Handle(ConsoleEngine& game, ControlObject& object, vec2& drawingPos)
        {
            for (auto& m : keyMap)
            {
                if (game.IsKeyPressed(m.first))
                {
                    m.second->Execute(game, object, drawingPos);
                }
            }            
        }

        auto SetCommand(int key) -> Command*&
        {
            return keyMap[key];
        }

    private:
        std::map<int, Command*> keyMap;
    };
}

#endif // !INPUT_HANDLER_H