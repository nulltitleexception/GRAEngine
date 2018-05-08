#ifndef GRAE_ENGINE_MOUSE_H
#define GRAE_ENGINE_MOUSE_H

namespace GRAE {
class Window;

class Mouse {
private:
    Window *window;
public:
    Mouse(Window *wind);
};
}

#endif //GRAE_ENGINE_MOUSE_H
