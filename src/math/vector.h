#ifndef GRAENGINE_VECTOR_H
#define GRAENGINE_VECTOR_H

#include "resource/gen.h"

namespace GRAE {
struct Vector4D {
    double x, y, z, w;

    explicit Vector4D(double c = 0);

    Vector4D(double _x, double _y, double _z = 0, double _w = 0);

    explicit Vector4D(Gen *gen);

    Vector4D operator+(const Vector4D v) const;

    Vector4D &operator+=(const Vector4D v);

    Vector4D operator-(const Vector4D v) const;

    Vector4D &operator-=(const Vector4D v);

    Vector4D operator*(double scalar) const;

    double operator*(Vector4D rhs) const;

    double dot(Vector4D rhs) const;

    Vector4D cross(Vector4D rhs) const;

    double sqmag() const;

    double mag() const;

    double componentInDirection(Vector4D rhs) const;

    Vector4D unit() const;

    void normalize();

    Vector4D projectedOnto(Vector4D rhs);
};
}

typedef GRAE::Vector4D vec4;


#endif //GRAENGINE_VECTOR_H
