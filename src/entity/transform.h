#ifndef GRAE_ENGINE_TRANSFORM_H
#define GRAE_ENGINE_TRANSFORM_H

#include "component.h"

namespace GRAE {
class Transform : public Component {
private:
    vec4 pos, rot, scale;
public:
    Transform();
    vec4 &getPos();

    vec4 &getRot();

    vec4 &getscale();

    mat4 asMatrix();
};
}


#endif //GRAE_ENGINE_TRANSFORM_H
