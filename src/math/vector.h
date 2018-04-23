#ifndef GRAENGINE_VECTOR_H
#define GRAENGINE_VECTOR_H


namespace GRAE {
struct Vector4D {
    double x, y, z, w;

    Vector4D(double c = 0);

    Vector4D(double _x, double _y, double _z = 0, double _w = 0);

    Vector4D operator+(const Vector4D v) const;

    Vector4D &operator+=(const Vector4D v);

    double operator*(Vector4D rhs) const;
};
}

typedef GRAE::Vector4D vec4;


#endif //GRAENGINE_VECTOR_H
