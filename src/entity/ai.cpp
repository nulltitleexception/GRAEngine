#include "ai.h"

namespace GRAE {
AI::AI() {}

virtual void AI::update(double dt, Entity *parent) {}

virtual vec4 AI::getGoalDirection() { return vec4(); }

SpinAI::SpinAI() : direction(0, 0, 1) {}

void SpinAI::update(double dt, Entity *parent) {
    direction += direction.cross(vec4(0, 1, 0, 0)) * 0.01;
    direction.normalize();
}

vec4 SpinAI::getGoalDirection() {
    return direction;
}
}