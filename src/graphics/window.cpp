#include "window.h"

#define GLFW_DLL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

#include "input/input.h"

#include "window_impl.hpp"

namespace GRAE {
Window::Window_Impl::Window_Impl(GLFWwindow *wind) : window(wind) {
}

enum WindowEvent {
    CLOSE, DESTROY
};

Window::Window() {}

Window::Window(GraphicsContext *g, WindowProperties &windowData) : properties(windowData) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, g->getProperties().GLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, g->getProperties().GLMinor);
    Impl = new Window_Impl(glfwCreateWindow(windowData.width, windowData.height,
                                            &windowData.title[0], NULL, NULL));
    if (!Impl->window) {
        throw std::runtime_error("Window creation failed");
    }
    acquire();
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(
            1);//0=vsync false | 1 = vsync true | 2 = half frame rate (purpose???)
    input = new InputContext(this);
}

Window::~Window() {
    delete input;
    if (Impl->window) {
        glfwDestroyWindow(Impl->window);
    }
}

Window::Window_Impl *Window::getImpl() {
    return Impl;
}

WindowProperties Window::getProperties() {
    return properties;
}

void Window::setTitle(std::string title) {
    glfwSetWindowTitle(Impl->window, title.c_str());
}

void Window::release() {
    lock.unlock();
    glfwMakeContextCurrent(nullptr);
}

void Window::acquire() {
    lock.lock();
    glfwMakeContextCurrent(Impl->window);
}

bool Window::closeRequested() {
    return glfwWindowShouldClose(Impl->window);
}

void Window::swap() {
    glfwSwapBuffers(Impl->window);
}

InputContext *Window::getInput() {
    return input;
}

}