#include "text.h"

namespace GRAE {
Text::Text(Mesh2D *m, Shader *s, Texture *t) : mesh(m), shader(s), texture(t) {}

Text::~Text() {
    delete mesh;
}

void Text::draw(mat4 m) {
    shader->bind();
    texture->bind();
    mesh->Render();
}
}