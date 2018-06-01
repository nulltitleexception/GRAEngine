#ifndef GRAE_ENGINE_MESH_H
#define GRAE_ENGINE_MESH_H

#include "Resources.h"
#include <glad/glad.h>

namespace GRAE {
class Mesh {
public:
    Mesh(std::string path, Resources *res);

    Mesh(float *verts, long vnum);

    ~Mesh();

    void create(float *verts, long vnum);

    void render();

    void renderVerts();

    void renderWireframe();

private:
    GLuint VAO, VBO;
    int vertnum;
};

class Mesh2D {
public:
    Mesh2D(float *verts, long vnum);

    ~Mesh2D();

    void create(float *verts, long vnum);

    void render();

private:
    GLuint VAO, VBO;
    int vertnum;
};
}

#endif //GRAE_ENGINE_MESH_H
