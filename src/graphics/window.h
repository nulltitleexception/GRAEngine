#ifndef GRAE_ENGINE_WINDOW_H
#define GRAE_ENGINE_WINDOW_H


#include "graphicscontext.h"

#define GLFW_DLL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <mutex>

namespace GRAE {
struct WindowProperties {
    std::string title;
    int width;
    int height;
};

static void
keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

class Window {
public:
    Window();

    Window(GraphicsContext *g, WindowProperties &windowData);//NOTE: acquire()s the window

    ~Window();

    GLFWwindow *getHandle();

    WindowProperties getProperties();

    void setTitle(std::string title);

    void release();//releases Window render context

    void acquire();//acquires Window render context

    bool closeRequested();

    void swap();

private:
    GLFWwindow *window;
    WindowProperties properties;
    std::mutex lock;
};
}


#endif //GRAE_ENGINE_WINDOW_H
