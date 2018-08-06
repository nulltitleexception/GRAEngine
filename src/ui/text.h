#ifndef GRAE_ENGINE_TEXT_H
#define GRAE_ENGINE_TEXT_H

#include "resource/mesh.h"
#include "resource/shader.h"
#include "resource/texture.h"

namespace GRAE {
class Text {
private:
    Mesh2D *mesh;
    Shader *shader;
    Texture *texture;
public:
    Text(Mesh2D *m, Shader *s, Texture *t);

    ~Text();

    void render(mat4 m = mat4());
};
}

#endif //GRAE_ENGINE_TEXT_H
