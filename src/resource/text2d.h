#ifndef GRAE_ENGINE_TEXT2D_H
#define GRAE_ENGINE_TEXT2D_H

#include "mesh.h"
#include "shader.h"
#include "texture.h"

namespace GRAE {
class Text2D {
private:
    Mesh2D *mesh;
    Shader *shader;
    Texture *texture;
    double width, height;
public:
    Text2D(Mesh2D *m, Shader *s, Texture *t, double w, double h);

    ~Text2D();

    void render(mat4 m = mat4());

    double getWidth();

    double getHeight();
};
}

#endif //GRAE_ENGINE_TEXT2D_H
