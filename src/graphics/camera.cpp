#include "camera.h"

#include "resource/shader.h"

namespace GRAE {
Camera::Camera() : perspective(false), nearP(0.1), farP(100), aspect(1), fov(90), width(1), height(1), distance(0) {}

void Camera::setPerspective() {
    perspective = true;
}

void Camera::setPerspective(double a, double f, double np, double fp) {
    perspective = true;
    nearP = np;
    farP = fp;
    aspect = a;
    fov = f;
}

void Camera::setOrthographic() {
    perspective = false;
}

void Camera::setOrthographic(int w, int h) {
    perspective = false;
    width = w;
    height = h;
}

Transform &Camera::getTransform() {
    return transform;
}

void Camera::setDistance(double d) {
    distance = d;
}

void Camera::bind() {
    if (perspective) {
        Shader::bindProjectionMatrix(MatUtil::getPerspective(fov, aspect, nearP, farP));
    } else {
        Shader::bindProjectionMatrix(MatUtil::getOrthographic(width, height));
    }
    Shader::bindViewMatrix(MatUtil::translation(0, 0, -distance) * transform.asMatrix());
}
}