#include "inputcontext.h"

#include "graphics/window_impl.hpp"

#define GLFW_DLL

#include <GLFW/glfw3.h>

namespace GRAE {
static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        std::cout << key << " pressed" << std::endl;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static void joystick_callback(int joy, int event) {
    if (event == GLFW_CONNECTED) {
        //joy disconnected
    } else if (event == GLFW_DISCONNECTED) {
        //joy connected
    }
}

InputContext::InputContext(Window *wind) : window(wind), keyboard(wind), mouse(wind) {
    glfwSetKeyCallback(window->getImpl()->window, keyCallback);
    glfwSetJoystickCallback(joystick_callback);
    controller_count = (GLFW_JOYSTICK_LAST - GLFW_JOYSTICK_1) + 1;
    controllers = new Controller *[controller_count];
    for (int i = 0; i < controller_count; i++) {
        controllers[i] = new Controller(i + GLFW_JOYSTICK_1);
    }
}

InputContext::~InputContext() {
    for (int i = 0; i < controller_count; i++) {
        delete controllers[i];
    }
    delete[] controllers;
}

Keyboard *InputContext::getKeyboard() {
    return &keyboard;
}

Controller *InputContext::getController(int num, bool relative) {
    if (relative) {
        for (int i = 0; i < controller_count; i++) {
            if (controllers[i]->exists()) {
                if (num == 0) {
                    return controllers[i];
                } else {
                    num--;
                }
            }
        }
        return controllers[num];
    } else {
        return controllers[num];
    }
}
}