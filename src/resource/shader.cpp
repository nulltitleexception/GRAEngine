#include "shader.h"

#include "system/file.h"
#include "system/log.h"

#include <glad/glad.h>

namespace GRAE {
void errCall(GLuint id) {
    GLint compileSuccess = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess == GL_FALSE) {
        GLint logLen = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
        std::vector<GLchar> errlog(logLen);
        glGetShaderInfoLog(id, logLen, &logLen, &errlog[0]);
        std::string slog(errlog.begin(), errlog.end());
        log->err << "Shader compilation failed!";
        log->verbose << slog;
    }
}

VertexShader::VertexShader(std::string text) {
    const char *shader_code = text.c_str();
    id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(id, 1, &shader_code, NULL);
    glCompileShader(id);
    errCall(id);
}

VertexShader::~VertexShader() {
    glDeleteShader(id);
}

FragmentShader::FragmentShader(std::string text) {
    const char *shader_code = text.c_str();
    id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(id, 1, &shader_code, NULL);
    glCompileShader(id);
    errCall(id);
}

FragmentShader::~FragmentShader() {
    glDeleteShader(id);
}

Shader::Shader(GRAE::Resources *res) {
    VertexShader vs(

#include "built_in/shader/default_vert.glsl"

    );
    FragmentShader fs(

#include "built_in/shader/default_frag.glsl"

    );
    id = glCreateProgram();
    glAttachShader(id, vs.get());
    glAttachShader(id, fs.get());
    glLinkProgram(id);
}

Shader::Shader(VertexShader vs, FragmentShader fs) {
    id = glCreateProgram();
    glAttachShader(id, vs.get());
    glAttachShader(id, fs.get());
    glLinkProgram(id);
}

Shader::Shader(std::string filePrefix, Resources *res, bool &success, std::string &reason) {
    if (filePrefix == "built_in/shader/color") {
        VertexShader vs(

#include "built_in/shader/color_vert.glsl"

        );
        FragmentShader fs(

#include "built_in/shader/color_frag.glsl"

        );
        id = glCreateProgram();
        glAttachShader(id, vs.get());
        glAttachShader(id, fs.get());
        glLinkProgram(id);
    } else {
        File vf(filePrefix + "_vert.glsl");
        if (!vf.getExists()){
            success = false;
            reason = "Vertex file not found!";
            return;
        }
        VertexShader vs(vf.getContents());
        File ff(filePrefix + "_frag.glsl");
        if (!ff.getExists()){
            success = false;
            reason = "Fragment file not found!";
            return;
        }
        FragmentShader fs(ff.getContents());
        id = glCreateProgram();
        glAttachShader(id, vs.get());
        glAttachShader(id, fs.get());
        glLinkProgram(id);
    }
    success = true;
}

Shader::~Shader() {
    glDeleteProgram(id);
}

namespace ShaderUtil {
static mat4 view, proj;
}

void Shader::bind() {
    glUseProgram(id);
    float f[4][4];
    ShaderUtil::view.toFloatArray(&(f[0][0]));
    glUniformMatrix4fv(5, 1, GL_FALSE, &f[0][0]);
    ShaderUtil::proj.toFloatArray(&(f[0][0]));
    glUniformMatrix4fv(6, 1, GL_FALSE, &f[0][0]);
}

GLint Shader::getUniformLocation(std::string s) {
    return glGetUniformLocation(id, s.c_str());
}

void Shader::setUniformInt(std::string s, int i) {
    glUniform1i(getUniformLocation(s), i);
}

void Shader::setUniformFloat(std::string s, float f) {
    glUniform1f(getUniformLocation(s), f);
}

void Shader::setUniformFloat(std::string s, float f0, float f1) {
    glUniform2f(getUniformLocation(s), f0, f1);
}

void Shader::setUniformFloat(std::string s, float f0, float f1, float f2) {
    glUniform3f(getUniformLocation(s), f0, f1, f2);
}

void Shader::setUniformFloat(std::string s, float f0, float f1, float f2, float f3) {
    glUniform4f(getUniformLocation(s), f0, f1, f2, f3);
}

void Shader::setUniformVec4(std::string s, vec4 v) {
    glUniform4f(getUniformLocation(s), v.x, v.y, v.z, v.w);
}

void Shader::bindModelMatrix(mat4 m) {
    float f[4][4];
    m.toFloatArray(&(f[0][0]));
    glUniformMatrix4fv(3, 1, GL_FALSE, &f[0][0]);
}

void Shader::bindEntityMatrix(mat4 m) {
    float f[4][4];
    m.toFloatArray(&(f[0][0]));
    glUniformMatrix4fv(4, 1, GL_FALSE, &f[0][0]);
}

void Shader::bindViewMatrix(mat4 m) {
    ShaderUtil::view = m;
    float f[4][4];
    m.toFloatArray(&(f[0][0]));
    glUniformMatrix4fv(5, 1, GL_FALSE, &f[0][0]);
}

void Shader::bindProjectionMatrix(mat4 m) {
    ShaderUtil::proj = m;
    float f[4][4];
    m.toFloatArray(&(f[0][0]));
    glUniformMatrix4fv(6, 1, GL_FALSE, &f[0][0]);
}
}