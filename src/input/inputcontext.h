#ifndef GRAE_ENGINE_INPUTCONTEXT_H
#define GRAE_ENGINE_INPUTCONTEXT_H

#include "graphics/graphics.h"
#include "controller.h"
#include "keyboard.h"
#include "mouse.h"

namespace GRAE {
class Window;

class InputContext {
private:
    Window *window;
    Keyboard keyboard;
    Mouse mouse;
    Controller** controllers;
    int controller_count;
public:
    InputContext(Window *wind);
    ~InputContext();
    Keyboard* getKeyboard();
    Mouse* getMouse();
    Controller* getController(int id, bool relative = false);
};
}

#endif //GRAE_ENGINE_INPUTCONTEXT_H
