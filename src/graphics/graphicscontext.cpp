#include "graphicscontext.h"

#include "system/log.h"

#define GLFW_DLL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GRAE {
GraphicsProperties::GraphicsProperties() {
}

GraphicsProperties::GraphicsProperties(Gen *gen) {
    GLMajor = gen->getInt("OpenGL Major");
    GLMinor = gen->getInt("OpenGL Minor");
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

std::string GraphicsContext::getImplementation() {
    std::stringstream ret;
    ret << "GLFW - Compiled V" << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION;
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    ret << " - Running V" << major << "." << minor << "." << revision;
    return ret.str();
}
}