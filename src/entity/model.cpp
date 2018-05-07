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

void Model::render() {
    mesh->Render();
}

void Model::draw(mat4 m){
    bind();
    Shader::bindEntityMatrix(m);
    render();
}
}