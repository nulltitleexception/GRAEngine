#include "vector.h"

#include <cmath>

namespace GRAE {
Vector4D::Vector4D(double c) : x(c), y(c), z(c), w(c) {}

Vector4D::Vector4D(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {}

Vector4D::Vector4D(GRAE::Gen *gen) {
    x = gen->getDouble("x");
    y = gen->getDouble("y");
    z = gen->getDouble("z");
    w = gen->getDouble("w");
}

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

Vector4D Vector4D::operator*(double scalar) const {
    return {x * scalar, y * scalar, z * scalar, w * scalar};
}

double Vector4D::operator*(Vector4D rhs) const {
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
}

double Vector4D::dot(Vector4D rhs) const {
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
}

Vector4D Vector4D::cross(Vector4D rhs) const {
    return Vector4D((y * rhs.z) - (z * rhs.y), (z * rhs.x) - (x * rhs.z), (x * rhs.y) - (y * rhs.x), 0);
}

double Vector4D::sqmag() const {
    return (x * x) + (y * y) + (z * z);
}

double Vector4D::mag() const {
    return sqrt(sqmag());
}

double Vector4D::componentInDirection(Vector4D rhs) const {
    return dot(rhs.unit());
}

Vector4D Vector4D::unit() const {
    double m = mag();
    return {x / m, y / m, z / m, w / m};
}

void Vector4D::normalize() {
    double m = mag();
    x /= m;
    y /= m;
    z /= m;
    w /= m;
}

Vector4D Vector4D::projectedOnto(Vector4D rhs) {
    return (*this) * (dot(rhs) / sqmag());
}
}