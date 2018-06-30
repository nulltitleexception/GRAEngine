#include "graphicscontext.h"

#include "system/log.h"

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
        throw std::runtime_error("Graphics Context failed to initialize");
    }
    initialized = true;
    log->high << "Graphics Context initialized successfully";
}

GraphicsContext::~GraphicsContext() {
    if (initialized) {
        glfwTerminate();
        log->high << "Graphics Context terminated";
    }
}

void GraphicsContext::poll() {
    glfwPollEvents();
}
}