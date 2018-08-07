#include "text2d.h"

namespace GRAE {
Text2D::Text2D(Mesh2D *m, Shader *s, Texture *t, double w, double h) : mesh(m), shader(s), texture(t), width(w), height(h) {}

Text2D::~Text2D() {
    delete mesh;
}

void Text2D::render(mat4 m) {
    shader->bind();
    Shader::bindModelMatrix(m);
    Shader::bindEntityMatrix(mat4(1));
    texture->bind();
    mesh->render();
}

double Text2D::getWidth() {
    return width;
}

double Text2D::getHeight() {
    return height;
}
}