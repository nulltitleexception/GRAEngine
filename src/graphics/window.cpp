#include "window.h"

#define GLFW_DLL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "input/input.h"
#include "system/log.h"

#include "window_impl.hpp"

#include "version/version.h"

namespace GRAE {
WindowProperties::WindowProperties() {}

WindowProperties::WindowProperties(GRAE::Gen *gen) {
    gen->getString("title", "GRAE Engine " + getVersionString());
    width = gen->getInt("resolution.x", 640);
    height = gen->getInt("resolution.y", 480);
    vsync = gen->getInt("vsync", 1);
    decorated = gen->getBool("decorated", true);
}

Window::Window_Impl::Window_Impl(GLFWwindow *wind) : window(wind) {
}

enum WindowEvent {
    CLOSE, DESTROY
};

Window::Window() {}

Window::Window(GraphicsContext *g, WindowProperties &windowData) : properties(windowData) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, g->getProperties().GLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, g->getProperties().GLMinor);
    glfwWindowHint(GLFW_DECORATED, properties.decorated);
    Impl = new Window_Impl(glfwCreateWindow(properties.width, properties.height,
                                            &properties.title[0], NULL, NULL));
    if (!Impl->window) {
        log->err << "Failed to create window";
        throw std::runtime_error("Window creation failed");
    }
    acquire();
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(properties.vsync);//0=vsync false | 1 = vsync true | 2 = half frame rate (purpose???)

    log->info << "OpenGL " << glGetString(GL_VERSION);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    input = new InputContext(this);
}

Window::~Window() {
    delete input;
    if (Impl->window) {
        glfwDestroyWindow(Impl->window);
    }
    delete Impl;
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

void Window::clear(bool color, bool depth) {
    glClear((color ? GL_COLOR_BUFFER_BIT : 0) | (depth ? GL_DEPTH_BUFFER_BIT : 0));
}

bool Window::closeRequested() {
    return (bool) glfwWindowShouldClose(Impl->window);
}

void Window::swap() {
    glfwSwapBuffers(Impl->window);
}

InputContext *Window::getInput() {
    return input;
}

}