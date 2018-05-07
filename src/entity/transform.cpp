#include "transform.h"

namespace GRAE {
Transform::Transform() : pos(0), rot(0), scale(1) {}

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
