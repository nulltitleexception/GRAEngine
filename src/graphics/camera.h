#ifndef GRAE_ENGINE_CAMERA_H
#define GRAE_ENGINE_CAMERA_H

#include "entity/transform.h"

namespace GRAE {
class Camera {
private:
    //projection attributes
    bool perspective;
    double nearP, farP, aspect, fov;
    int width, height;
    //view attributes
    Transform transform;
    double distance;
public:
    Camera();

    void setPerspective();

    void setPerspective(double a, double f, double np, double fp);

    void setOrthographic();

    void setOrthographic(int w, int h);

    Transform &getTransform();

    void setDistance(double d);

    void bind();
};
}


#endif //GRAE_ENGINE_CAMERA_H
