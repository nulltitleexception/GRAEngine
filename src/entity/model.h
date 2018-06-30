#ifndef GRAE_ENGINE_MODEL_H
#define GRAE_ENGINE_MODEL_H

#include "resource/resource.h"
#include "graphics/graphics.h"

namespace GRAE {
class Model : public Component {
private:
    Material *material;
    Mesh *mesh;
public:
    Model(std::string s, Resources *res, bool& success, std::string& reason);

    void bind();

    void render(mat4 m);

    void renderOutline(mat4 m, vec4 c = vec4(1));
};
}


#endif //GRAE_ENGINE_MODEL_H
