#include "system.h"

#define GLFW_DLL

#include <GLFW/glfw3.h>

namespace GRAE{
double System::getTime(){
    return glfwGetTime();
}
}
