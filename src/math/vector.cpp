#include "vector.h"

namespace GRAE {
Vector4D::Vector4D(double c) : x(c), y(c), z(c), w(c) {}

Vector4D::Vector4D(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {}

Vector4D Vector4D::operator+(const Vector4D v) const {
    return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4D &Vector4D::operator+=(const Vector4D v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

double Vector4D::operator*(Vector4D rhs) const {
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
}
}