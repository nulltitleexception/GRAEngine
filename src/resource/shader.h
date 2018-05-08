#ifndef GRAE_ENGINE_SHADER_H
#define GRAE_ENGINE_SHADER_H

#include "math/math.h"
#include "resources.h"
#include <glad/glad.h>
#include <string>

namespace GRAE {
class VertexShader {
public:
    VertexShader(std::string text);

    ~VertexShader();

    inline GLuint get() {
        return id;
    }

private:
    GLuint id;
};

class FragmentShader {
public:
    FragmentShader(std::string text);

    ~FragmentShader();

    inline GLuint get() {
        return id;
    }

private:
    GLuint id;
};

class Shader {
public:
    Shader(VertexShader vs, FragmentShader fs);

    Shader(std::string filePrefix, Resources *res);

    Shader() {}

    ~Shader();

    void bind();

    GLint getUniformLocation(std::string s);

    void setUniformInt(std::string s, int i);

    void setUniformFloat(std::string s, float f);

    void setUniformFloat(std::string s, float f0, float f1);

    void setUniformFloat(std::string s, float f0, float f1, float f2);

    void setUniformFloat(std::string s, float f0, float f1, float f2, float f3);

    static void bindModelMatrix(mat4 m);

    static void bindEntityMatrix(mat4 m);

    static void bindViewMatrix(mat4 m);

    static void bindProjectionMatrix(mat4 m);

private:
    GLuint id;
};
}



#endif //GRAE_ENGINE_SHADER_H
