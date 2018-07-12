#ifndef GRAE_ENGINE_MODEL_H
#define GRAE_ENGINE_MODEL_H

#include "resource/material.h"
#include "resource/mesh.h"
#include "resource/resources.h"
#include "graphics/graphics.h"

namespace GRAE {
class Model : public Component {
private:
    Resources *resources;
    Material *material;
    Mesh *mesh;
public:
    explicit Model(Resources *res);

    Model(std::string s, Resources *res, bool &success, std::string &reason);

    void bind();

    void render(mat4 m);

    void renderWithOutline(mat4 m, vec4 c = vec4(1));

    void renderOutlineOnly(mat4 m, vec4 c = vec4(1));
};
}


#endif //GRAE_ENGINE_MODEL_H
