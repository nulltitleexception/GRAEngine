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

    void renderWireframe();

private:
    unsigned int VAO, VBO;
    int vertnum;
public:
    static Mesh2D *createBox(float xmin, float ymin, float xmax, float ymax) {
        float v[24];
        v[(0 * 24)] = xmin;
        v[(0 * 24) + 1] = ymin;
        v[(0 * 24) + 2] = 0;
        v[(0 * 24) + 3] = 0;
        v[(0 * 24) + 4] = xmax;
        v[(0 * 24) + 5] = ymin;
        v[(0 * 24) + 6] = 1;
        v[(0 * 24) + 7] = 0;
        v[(0 * 24) + 8] = xmax;
        v[(0 * 24) + 9] = ymax;
        v[(0 * 24) + 10] = 1;
        v[(0 * 24) + 11] = 1;
        v[(0 * 24) + 12] = xmin;
        v[(0 * 24) + 13] = ymin;
        v[(0 * 24) + 14] = 0;
        v[(0 * 24) + 15] = 0;
        v[(0 * 24) + 16] = xmax;
        v[(0 * 24) + 17] = ymax;
        v[(0 * 24) + 18] = 1;
        v[(0 * 24) + 19] = 1;
        v[(0 * 24) + 20] = xmin;
        v[(0 * 24) + 21] = ymax;
        v[(0 * 24) + 22] = 0;
        v[(0 * 24) + 23] = 1;
        return new Mesh2D(v, 6);
    }
};
}

#endif //GRAE_ENGINE_MESH_H
