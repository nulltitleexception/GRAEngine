#include "matrix.h"

#define _USE_MATH_DEFINES

#include <math.h>

namespace GRAE {

Matrix4x4D::Matrix4x4D(double diag) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                m[i][j] = diag;
            } else {
                m[i][j] = 0;
            }
        }
    }
}

Matrix4x4D &Matrix4x4D::operator*=(Matrix4x4D rhs) {
    Matrix4x4D ret;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ret.m[i][j] = (m[0][j] * rhs.m[i][0]) + (m[1][j] * rhs.m[i][1]) + (m[2][j] * rhs.m[i][2]) +
                          (m[3][j] * rhs.m[i][3]);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = ret.m[i][j];
        }
    }
    return *this;
}

Matrix4x4D Matrix4x4D::operator*(Matrix4x4D rhs) {
    Matrix4x4D ret;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ret.m[i][j] = (m[0][j] * rhs.m[i][0]) + (m[1][j] * rhs.m[i][1]) + (m[2][j] * rhs.m[i][2]) +
                          (m[3][j] * rhs.m[i][3]);
        }
    }
    return ret;
}

Vector4D Matrix4x4D::operator*(Vector4D v) {
    Vector4D ret;
    ret.x = (m[0][0] * v.x) + (m[1][0] * v.y) + (m[2][0] * v.z) + (m[3][0] * v.x);
    ret.y = (m[0][1] * v.x) + (m[1][1] * v.y) + (m[2][1] * v.z) + (m[3][1] * v.w);
    ret.z = (m[0][2] * v.x) + (m[1][2] * v.y) + (m[2][2] * v.z) + (m[3][2] * v.w);
    ret.w = (m[0][3] * v.x) + (m[1][3] * v.y) + (m[2][3] * v.z) + (m[3][3] * v.w);
    return ret;
}

void Matrix4x4D::toFloatArray(float *f) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            f[(i * 4) + j] = (float) (m[i][j]);
        }
    }
}

namespace MatUtil {

mat4 translation(double x, double y, double z) {
    mat4 mat(1);
    mat.m[3][0] = x;
    mat.m[3][1] = y;
    mat.m[3][2] = z;
    return mat;
}

mat4 scale(double x, double y, double z) {
    mat4 mat(1);
    mat.m[0][0] = x;
    mat.m[1][1] = y;
    mat.m[2][2] = z;
    return mat;
}

mat4 rotationX(double r) {
    mat4 mat(1);
    mat.m[1][1] = cos(r);
    mat.m[2][2] = cos(r);
    mat.m[1][2] = sin(r);
    mat.m[2][1] = -sin(r);
    return mat;
}

mat4 rotationY(double r) {
    mat4 mat(1);
    mat.m[0][0] = cos(r);
    mat.m[2][2] = cos(r);
    mat.m[0][2] = -sin(r);
    mat.m[2][0] = sin(r);
    return mat;
}

mat4 rotationZ(double r) {
    mat4 mat(1);
    mat.m[0][0] = cos(r);
    mat.m[1][1] = cos(r);
    mat.m[0][1] = sin(r);
    mat.m[1][0] = -sin(r);
    return mat;
}

Matrix4x4D getLookRotation(vec4 direction, vec4 up) {
    mat4 mat(1);
    vec4 z = direction;
    vec4 x = up.cross(z);
    vec4 y = z.cross(x);
    mat.m[0][0] = x.x;
    mat.m[0][1] = x.y;
    mat.m[0][2] = x.z;
    mat.m[1][0] = y.x;
    mat.m[1][1] = y.y;
    mat.m[1][2] = y.z;
    mat.m[2][0] = z.x;
    mat.m[2][1] = z.y;
    mat.m[2][2] = z.z;
}

mat4 getOrthographic(double width, double height) {
    mat4 mat(1);
    mat.m[0][0] = 2 / width;
    mat.m[1][1] = -2 / height;
    mat.m[3][0] = -1;
    mat.m[3][1] = 1;
    return mat;
}

mat4 getPerspective(double fov, double aspect, double nearPlane, double farPlane) {
    mat4 mat(0);
    mat.m[0][0] = 1.0 / (tan(M_PI * fov / 360) * aspect);
    mat.m[1][1] = 1.0 / tan(M_PI * fov / 360);
    mat.m[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
    mat.m[3][2] = (2 * farPlane * nearPlane) / (nearPlane - farPlane);
    mat.m[2][3] = -1;
    return mat;
}
}
}