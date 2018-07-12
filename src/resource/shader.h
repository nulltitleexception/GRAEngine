#ifndef GRAE_ENGINE_SHADER_H
#define GRAE_ENGINE_SHADER_H

#include "math/math.h"
#include "resources.h"
#include <string>

namespace GRAE {
class VertexShader {
private:
    unsigned int id;

public:
    VertexShader(std::string text);

    ~VertexShader();

    inline unsigned int get() {
        return id;
    }
};

class FragmentShader {
private:
    unsigned int id;

public:
    FragmentShader(std::string text);

    ~FragmentShader();

    inline unsigned int get() {
        return id;
    }
};

class Shader {
private:
    unsigned int id;

public:
    explicit Shader(Resources *res);

    Shader(VertexShader vs, FragmentShader fs);

    Shader(std::string filePrefix, Resources *res, bool &success, std::string &reason);

    Shader() {}

    ~Shader();

    void bind();

    int getUniformLocation(std::string s);

    void setUniformInt(std::string s, int i);

    void setUniformFloat(std::string s, float f);

    void setUniformFloat(std::string s, float f0, float f1);

    void setUniformFloat(std::string s, float f0, float f1, float f2);

    void setUniformFloat(std::string s, float f0, float f1, float f2, float f3);

    void setUniformVec4(std::string s, vec4 v);

    static void bindModelMatrix(mat4 m);

    static void bindEntityMatrix(mat4 m);

    static void bindViewMatrix(mat4 m);

    static void bindProjectionMatrix(mat4 m);
};
}


#endif //GRAE_ENGINE_SHADER_H
