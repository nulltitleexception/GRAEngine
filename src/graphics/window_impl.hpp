#define GLFW_DLL

#include <GLFW/glfw3.h>

namespace GRAE {
class Window::Window_Impl {
public:
    GLFWwindow *window;
public:
    Window_Impl(GLFWwindow *wind);
};
}