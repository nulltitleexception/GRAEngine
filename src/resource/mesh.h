#ifndef GRAE_ENGINE_MESH_H
#define GRAE_ENGINE_MESH_H

#include "Resources.h"
#include <glad/glad.h>

namespace GRAE {
class Mesh {
public:
    Mesh(std::string path, Resources *res);

    Mesh(float *verts, long vnum);

    void create(float *verts, long vnum);

    void Render();

private:
    GLuint VAO, VBO;
    int vertnum;
};
}

#endif //GRAE_ENGINE_MESH_H
