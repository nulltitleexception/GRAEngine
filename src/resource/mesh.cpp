#include "mesh.h"

namespace GRAE {
namespace Util {
std::vector<std::string> SplitString(std::string s, std::string delimiter) {
    std::vector<std::string> tokens;
    int pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        tokens.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}
}

Mesh::Mesh(std::string path, Resources *res) {
    File cache(path + ".msh");
    if (cache.getExists()) {
        char *contents = cache.getBytes();
        create((float *) (((int *) contents) + 1), *((int *) contents));
        delete contents;
    } else {
        File file(path + ".obj");
        std::vector<std::string> lines = file.getLines();
        int facenum = 0;
        int vertnum = 0;
        int normnum = 0;
        int uvnum = 0;
        for (int i = 0; i < lines.size(); i++) {
            if (lines[i][0] == 'f') {
                facenum++;
            } else if (lines[i][0] == 'v') {
                if (lines[i][1] == 'n') {
                    normnum++;
                } else if (lines[i][1] == 't') {
                    uvnum++;
                } else {
                    vertnum++;
                }
            }
        }
        float *rawverts = new float[vertnum * 3];
        int vertpos = 0;
        float *rawnorms = new float[normnum * 3];
        int normpos = 0;
        float *rawuvs = new float[uvnum * 2];
        int uvpos = 0;
        for (int i = 0; i < lines.size(); i++) {
            if (lines[i][0] == 'v') {
                if (lines[i][1] == 'n') {
                    std::vector<std::string> components = Util::SplitString(lines[i], " ");
                    rawnorms[normpos] = std::stof(components[1]);
                    rawnorms[normpos + 1] = std::stof(components[2]);
                    rawnorms[normpos + 2] = std::stof(components[3]);
                    normpos += 3;
                } else if (lines[i][1] == 't') {
                    std::vector<std::string> components = Util::SplitString(lines[i], " ");
                    rawuvs[uvpos] = std::stof(components[1]);
                    rawuvs[uvpos + 1] = 1 - std::stof(components[2]);
                    uvpos += 2;
                } else {
                    std::vector<std::string> components = Util::SplitString(lines[i], " ");
                    rawverts[vertpos] = std::stof(components[1]);
                    rawverts[vertpos + 1] = std::stof(components[2]);
                    rawverts[vertpos + 2] = std::stof(components[3]);
                    vertpos += 3;
                }
            }
        }
        long contentSize = (facenum * 24 * sizeof(float)) + (sizeof(int));
        char *contents = new char[contentSize];
        float *verts = ((float *) ((int *) contents) + 1);
        int facepos = 0;
        for (int i = 0; i < lines.size(); i++) {
            if (lines[i][0] == 'f') {
                std::vector<std::string> components = GRAE::Util::SplitString(lines[i], " ");
                for (int k = 0; k < 3; k++) {
                    std::vector<std::string> c = GRAE::Util::SplitString(components[k + 1], "/");
                    int vpos = (std::stoi(c[0]) - 1) * 3;
                    int upos = (std::stoi(c[1]) - 1) * 2;
                    int npos = (std::stoi(c[2]) - 1) * 3;
                    for (int j = 0; j < 3; j++) {
                        verts[facepos + j] = rawverts[vpos + j];
                    }
                    for (int j = 0; j < 3; j++) {
                        verts[facepos + j + 3] = rawnorms[npos + j];
                    }
                    for (int j = 0; j < 2; j++) {
                        verts[facepos + j + 6] = rawuvs[upos + j];
                    }
                    facepos += 8;
                }
            }
        }
        ((int *) contents)[0] = facenum * 3;
        cache.createOrOverwrite(contents, contentSize);
        create(verts, facenum * 3);
        delete rawverts;
        delete rawnorms;
        delete rawuvs;
        delete contents;
    }
}

Mesh::Mesh(float *verts, long vnum) {
    this->create(verts, vnum);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::create(float *verts, long vnum) {
    vertnum = vnum;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertnum * 8 * sizeof(float), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 8, (void *) (sizeof(float) * 3));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float) * 8, (void *) (sizeof(float) * 6));
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Mesh::render() {
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDrawArrays(GL_TRIANGLES, 0, vertnum);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Mesh::renderVerts() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDrawArrays(GL_TRIANGLES, 0, vertnum);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Mesh::renderWireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDrawArrays(GL_TRIANGLES, 0, vertnum);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Mesh2D::Mesh2D(float *verts, long vnum) {
    this->create(verts, vnum);
}

Mesh2D::~Mesh2D() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh2D::create(float *verts, long vnum) {
    vertnum = vnum;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertnum * 4 * sizeof(float), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 4, (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 4, (void *) (sizeof(float) * 2));
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Mesh2D::render() {
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, vertnum);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
}