#include "matrix.h"

#include <cmath>

const double PI = 3.14159265358979323846;

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

inline double det2x2(double m[4][4], int x, int y) {
    return (m[x % 4][y % 4] * m[(x + 1) % 4][(y + 1) % 4]) - (m[(x + 1) % 4][y % 4] * m[x % 4][(y + 1) % 4]);
}

inline double det3x3(double m[4][4], int x, int y) {
    return (m[x % 4][y % 4] * det2x2(m, (x + 1) % 4, (y + 1) % 4)) -
           (m[(x + 1) % 4][y % 4] * det2x2(m, (x + 2) % 4, (y + 1) % 4)) +
           (m[(x + 2) % 4][y % 4] * det2x2(m, (x + 3) % 4, (y + 1) % 4));
}

double Matrix4x4D::determinant() {
    return (m[0][3] * det3x3(m, 1, 0)) -
           (m[1][3] * det3x3(m, 2, 0)) +
           (m[2][3] * det3x3(m, 3, 0)) -
           (m[3][3] * det3x3(m, 0, 0));
}

Matrix4x4D Matrix4x4D::getTranspose() {
    mat4 mat;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat.m[i][j] = m[j][i];
        }
    }
    return mat;
}

Matrix4x4D Matrix4x4D::getAdjoint() {
    mat4 mat;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat.m[j][i] = (i % 2 == j % 2) ?: -det3x3(m, i + 1, j + 1);
        }
    }
    return mat;
}

Matrix4x4D Matrix4x4D::getInverse() {
    mat4 mat = getAdjoint();
    double det = determinant();
    double zero = 0.000001;
    if (det < zero && det > -zero) {
        log->err << "matrix is singular!";
    }
    double invDet = 1.0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat.m[i][j] *= invDet;
        }
    }
    return mat;
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
    mat.m[1][1] = std::cos(r);
    mat.m[2][2] = std::cos(r);
    mat.m[1][2] = std::sin(r);
    mat.m[2][1] = -std::sin(r);
    return mat;
}

mat4 rotationY(double r) {
    mat4 mat(1);
    mat.m[0][0] = std::cos(r);
    mat.m[2][2] = std::cos(r);
    mat.m[0][2] = -std::sin(r);
    mat.m[2][0] = std::sin(r);
    return mat;
}

mat4 rotationZ(double r) {
    mat4 mat(1);
    mat.m[0][0] = std::cos(r);
    mat.m[1][1] = std::cos(r);
    mat.m[0][1] = std::sin(r);
    mat.m[1][0] = -std::sin(r);
    return mat;
}

Matrix4x4D rotationAxis(double r, vec4 axis) {
    axis.normalize();
    mat4 mat(1);
    mat.m[0][0] = ((axis.x * axis.x) * (1 - std::cos(r))) + std::cos(r);
    mat.m[1][0] = ((axis.x * axis.y) * (1 - std::cos(r))) - (axis.z * std::sin(r));
    mat.m[2][0] = ((axis.x * axis.z) * (1 - std::cos(r))) + (axis.y * std::sin(r));
    mat.m[0][1] = ((axis.y * axis.x) * (1 - std::cos(r))) + (axis.z * std::sin(r));
    mat.m[1][1] = ((axis.y * axis.y) * (1 - std::cos(r))) + std::cos(r);
    mat.m[2][1] = ((axis.y * axis.z) * (1 - std::cos(r))) - (axis.x * std::sin(r));
    mat.m[0][2] = ((axis.z * axis.x) * (1 - std::cos(r))) - (axis.y * std::sin(r));
    mat.m[1][2] = ((axis.z * axis.y) * (1 - std::cos(r))) + (axis.x * std::sin(r));
    mat.m[2][2] = ((axis.z * axis.z) * (1 - std::cos(r))) + std::cos(r);
    return mat;
}

Matrix4x4D rotationEulerVector(vec4 axis) {
    return rotationAxis(axis.mag(), axis.unit());
}

Matrix4x4D getLookRotation(vec4 direction, vec4 up) {
    mat4 mat(1);
    vec4 z = direction.unit();
    vec4 x = up.cross(z).unit();
    vec4 y = z.cross(x).unit();
    mat.m[0][0] = x.x;
    mat.m[0][1] = x.y;
    mat.m[0][2] = x.z;
    mat.m[1][0] = y.x;
    mat.m[1][1] = y.y;
    mat.m[1][2] = y.z;
    mat.m[2][0] = z.x;
    mat.m[2][1] = z.y;
    mat.m[2][2] = z.z;
    return mat;
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
    mat.m[0][0] = 1.0 / (std::tan(PI * fov / 360) * aspect);
    mat.m[1][1] = 1.0 / std::tan(PI * fov / 360);
    mat.m[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
    mat.m[3][2] = (2 * farPlane * nearPlane) / (nearPlane - farPlane);
    mat.m[2][3] = -1;
    return mat;
}
}
}