#ifndef GRAE_ENGINE_MODEL_H
#define GRAE_ENGINE_MODEL_H

#include "resource/resource.h"
#include "graphics/graphics.h"

namespace GRAE {
class Model : public Component{
private:
    Material *material;
    Mesh *mesh;
public:
    Model(std::string s, Resources* res);
    void bind();
    void render();
    void draw(mat4 m);
};
}


#endif //GRAE_ENGINE_MODEL_H
