#include "text2d.h"

namespace GRAE {
Text2D::Text2D(Mesh2D *m, Shader *s, Texture *t) : mesh(m), shader(s), texture(t) {}

Text2D::~Text2D() {
    delete mesh;
}

void Text2D::render(mat4 m) {
    shader->bind();
    texture->bind();
    mesh->render();
}
}