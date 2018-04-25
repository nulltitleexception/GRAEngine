#include "graphicscontext.h"

#include <iostream>
#include <stdexcept>

#define GLFW_DLL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GRAE {
GraphicsProperties::GraphicsProperties() {
}

GraphicsProperties::GraphicsProperties(Config *cfg) {
GLMajor = cfg->getInt("OpenGL Major");
GLMinor = cfg->getInt("OpenGL Minor");
}

GraphicsContext::GraphicsContext() : initialized(false) {
}

GraphicsContext::GraphicsContext(GraphicsProperties &gp) : initialized(false) {
    properties = gp;
    if (!glfwInit()) {
        throw std::runtime_error("GLFW failed to initialize");
    }
    initialized = true;
    std::cout << "GLFW initialized successfully" << std::endl;
}

GraphicsContext::~GraphicsContext() {
    if (initialized) {
        glfwTerminate();
        std::cout << "GLFW terminated" << std::endl;
    }
}

void GraphicsContext::poll() {
    glfwPollEvents();
}
}