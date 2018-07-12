#include "model.h"

#include "resource/config.h"

#include <glad/glad.h>

namespace GRAE {
Model::Model(GRAE::Resources *res) : resources(res) {
    material = res->get<Material>();
    mesh = res->get<Mesh>();
}

Model::Model(std::string s, Resources *res, bool &success, std::string &reason) : resources(res) {
    Config *cfg = res->getFromRoot<Config>(s + ".mdl");
    material = res->get<Material>(cfg->getString("material"));
    mesh = res->get<Mesh>(cfg->getString("mesh"));
    success = true;
}

void Model::bind() {
    material->bind();
}

void Model::render(mat4 m) {
    bind();
    Shader::bindModelMatrix(mat4(1));
    Shader::bindEntityMatrix(m);
    mesh->render();
}

void Model::renderWithOutline(mat4 m, vec4 c) {
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);

    glEnable(GL_STENCIL_TEST);

    glStencilFunc(GL_ALWAYS, 1, -1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    bind();
    Shader::bindModelMatrix(mat4(1));
    Shader::bindEntityMatrix(m);
    mesh->render();

    glStencilFunc(GL_NOTEQUAL, 1, -1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glLineWidth(3);
    Shader* colorShader = resources->getFromRoot<Shader>("built_in/shader/color");
    colorShader->bind();
    colorShader->setUniformVec4("color", c);
    Shader::bindModelMatrix(mat4(1));
    Shader::bindEntityMatrix(m);
    mesh->renderWireframe();

    glDisable(GL_STENCIL_TEST);
}

void Model::renderOutlineOnly(mat4 m, vec4 c) {
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);

    glEnable(GL_STENCIL_TEST);

    glStencilFunc(GL_ALWAYS, 1, -1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_FALSE);

    bind();
    Shader::bindModelMatrix(mat4(1));
    Shader::bindEntityMatrix(m);
    mesh->render();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);

    glStencilFunc(GL_NOTEQUAL, 1, -1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glLineWidth(3);
    Shader* colorShader = resources->getFromRoot<Shader>("built_in/shader/color");
    colorShader->bind();
    colorShader->setUniformVec4("color", c);
    Shader::bindModelMatrix(mat4(1));
    Shader::bindEntityMatrix(m);
    mesh->renderWireframe();

    glDisable(GL_STENCIL_TEST);
}
}