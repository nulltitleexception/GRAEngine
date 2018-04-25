#include "window.h"
#include <iostream>
#include <stdexcept>

namespace GRAE {
enum WindowEvent {
    CLOSE, DESTROY
};

static void
keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        std::cout << key << " pressed" << std::endl;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

Window::Window() {}

Window::Window(GraphicsContext *g, WindowProperties &windowData) : properties(windowData) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, g->getProperties().GLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, g->getProperties().GLMinor);
    window = glfwCreateWindow(windowData.width, windowData.height,
                              &windowData.title[0], NULL, NULL);
    if (!window) {
        throw std::runtime_error("Window creation failed");
    }
    this->acquire();
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSetKeyCallback(window, keyCallback);
    glfwSwapInterval(
            1);//0=vsync false | 1 = vsync true | 2 = half frame rate (purpose???)
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
}

GLFWwindow *Window::getHandle() {
    return window;
}

WindowProperties Window::getProperties() {
    return properties;
}

void Window::setTitle(std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

void Window::release() {
    lock.unlock();
    glfwMakeContextCurrent(nullptr);
}

void Window::acquire() {
    lock.lock();
    glfwMakeContextCurrent(window);
}

bool Window::closeRequested() {
    return glfwWindowShouldClose(window);
}

void Window::swap() {
    glfwSwapBuffers(window);
}

}