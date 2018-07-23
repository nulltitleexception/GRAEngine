#ifndef GRAENGINE_MATRIX_H
#define GRAENGINE_MATRIX_H

#include "vector.h"

namespace GRAE {

class Matrix4x4D {
public:
    double m[4][4];

    Matrix4x4D(double diag = 1);

    Matrix4x4D &operator*=(Matrix4x4D rhs);

    Matrix4x4D operator*(Matrix4x4D rhs);

    Vector4D operator*(Vector4D v);

    void toFloatArray(float *f);
};

namespace MatUtil {

Matrix4x4D translation(double x, double y, double z);

Matrix4x4D scale(double x, double y, double z);

Matrix4x4D rotationX(double r);

Matrix4x4D rotationY(double r);

Matrix4x4D rotationZ(double r);

Matrix4x4D getLookRotation(vec4 direction, vec4 up = {0, 1, 0, 0});

Matrix4x4D getOrthographic(double width, double height);

Matrix4x4D getPerspective(double fov, double aspect, double nearPlane, double farPlane);

}

}

typedef GRAE::Matrix4x4D mat4;

#endif //GRAENGINE_MATRIX_H
