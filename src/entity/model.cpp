#include "model.h"

#include "resource/config.h"

namespace GRAE {
Model::Model(std::string s, Resources *res) {
    Config cfg(s + ".mdl", res);
    material = res->get<Material>(cfg.getString("material"));
    mesh = res->get<Mesh>(cfg.getString("mesh"));
}

void Model::bind() {
    material->bind();
}

void Model::render(mat4 m){
    bind();
    Shader::bindModelMatrix(mat4(1));
    Shader::bindEntityMatrix(m);
    mesh->render();
}

void Model::renderOutline(mat4 m, vec4 c){
    Shader::bindDefaultShader(c);
    Shader::bindModelMatrix(mat4(1));
    Shader::bindEntityMatrix(m);
    mesh->renderWireframe();
}
}