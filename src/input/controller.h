#ifndef GRAE_ENGINE_CONTROLLER_H
#define GRAE_ENGINE_CONTROLLER_H

namespace GRAE {
class Controller {
private:
    int id;
public:
    Controller();

    Controller(int num);

    bool exists();

    int axisCount();

    float getAxis(int num);

    int buttonCount();

    bool getButton(int num);
};
}

#endif //GRAE_ENGINE_CONTROLLER_H
