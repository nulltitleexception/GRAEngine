#ifndef GRAE_ENGINE_MESH_H
#define GRAE_ENGINE_MESH_H

#include "Resources.h"

namespace GRAE {
class Mesh {
public:
    explicit Mesh(Resources *res);

    Mesh(std::string path, Resources *res, bool &success, std::string &reason);

    Mesh(float *verts, long vnum);

    ~Mesh();

    void create(float *verts, long vnum);

    void render();

    void renderVerts();

    void renderWireframe();

private:
    unsigned int VAO, VBO;
    int vertnum;
};

class Mesh2D {
public:
    Mesh2D(float *verts, long vnum);

    ~Mesh2D();

    void create(float *verts, long vnum);

    void render();

private:
    unsigned int VAO, VBO;
    int vertnum;
};
}

#endif //GRAE_ENGINE_MESH_H
