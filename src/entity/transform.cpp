#include "transform.h"

namespace GRAE {
Transform::Transform() : pos(), rot(), scale(1) {}

Transform::Transform(Gen *gen) : pos(), rot(), scale(1) {
    if (gen) {
        if (gen->getSubValues("pos")) {
            pos = vec4(gen->getSubValues("pos"));
        }
        if (gen->getSubValues("rot")) {
            rot = vec4(gen->getSubValues("rot"));
        }
        if (gen->getSubValues("scale")) {
            scale = vec4(gen->getSubValues("scale"));
        }
    }
}

vec4 &Transform::getPos() {
    return pos;
}

vec4 &Transform::getRot() {
    return rot;
}

vec4 &Transform::getscale() {
    return scale;
}

mat4 Transform::asMatrix() {
    return MatUtil::translation(pos.x, pos.y, pos.z) * MatUtil::rotationX(rot.x) * MatUtil::rotationZ(rot.z) *
           MatUtil::rotationY(rot.y) * MatUtil::scale(scale.x, scale.y, scale.z);
}
}
