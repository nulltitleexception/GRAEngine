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
        v[1] = ymin;
        v[2] = 0;
        v[3] = 0;
        v[4] = xmax;
        v[5] = ymin;
        v[6] = 1;
        v[7] = 0;
        v[8] = xmax;
        v[9] = ymax;
        v[10] = 1;
        v[11] = 1;
        v[12] = xmin;
        v[13] = ymin;
        v[14] = 0;
        v[15] = 0;
        v[16] = xmax;
        v[17] = ymax;
        v[18] = 1;
        v[19] = 1;
        v[20] = xmin;
        v[21] = ymax;
        v[22] = 0;
        v[23] = 1;
        return new Mesh2D(v, 6);
    }

    static Mesh2D *createBorders(float xmin, float ymin, float xmax, float ymax) {
        float v[48];
        v[0] = xmin;
        v[1] = ymin;
        v[2] = 0;
        v[3] = 0;
        v[4] = xmin;
        v[5] = ymin;
        v[6] = 0;
        v[7] = 0;
        v[8] = xmax;
        v[9] = ymin;
        v[10] = 1;
        v[11] = 0;
        v[12] = xmax;
        v[13] = ymin;
        v[14] = 1;
        v[15] = 0;
        v[16] = xmax;
        v[17] = ymin;
        v[18] = 1;
        v[19] = 0;
        v[20] = xmax;
        v[21] = ymax;
        v[22] = 1;
        v[23] = 1;
        v[24] = xmax;
        v[25] = ymax;
        v[26] = 1;
        v[27] = 1;
        v[28] = xmax;
        v[29] = ymax;
        v[30] = 1;
        v[31] = 1;
        v[32] = xmin;
        v[33] = ymax;
        v[34] = 0;
        v[35] = 1;
        v[36] = xmin;
        v[37] = ymax;
        v[38] = 0;
        v[39] = 1;
        v[40] = xmin;
        v[41] = ymax;
        v[42] = 0;
        v[43] = 1;
        v[44] = xmin;
        v[45] = ymin;
        v[46] = 0;
        v[47] = 0;
        return new Mesh2D(v, 12);
    }
};
}

#endif //GRAE_ENGINE_MESH_H
