#include "controller.h"

#define GLFW_DLL

#include <GLFW/glfw3.h>

namespace GRAE {
Controller::Controller() : id(0) {}

Controller::Controller(int num) : id(num) {}

bool Controller::exists() {
    return id >= GLFW_JOYSTICK_1 && id <= GLFW_JOYSTICK_LAST && glfwJoystickPresent(id);
}

int Controller::axisCount() {
    int count;
    const float *axes = glfwGetJoystickAxes(id, &count);
    return count;
}

float Controller::getAxis(int num) {
    int count;
    const float *axes = glfwGetJoystickAxes(id, &count);
    return axes[num];
}

int Controller::buttonCount() {
    int count;
    const unsigned char *buttons = glfwGetJoystickButtons(id, &count);
    return count;
}

bool Controller::getButton(int num) {
    int count;
    const unsigned char *buttons = glfwGetJoystickButtons(id, &count);
    return buttons[num] == GLFW_PRESS;
}

}