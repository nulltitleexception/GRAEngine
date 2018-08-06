#ifndef GRAE_ENGINE_GAME_H
#define GRAE_ENGINE_GAME_H

#include "ui/menucontainer.h"
#include "world/world.h"
#include "graphics/window.h"
#include "graphics/graphicscontext.h"
#include "resource/resources.h"

namespace GRAE {
class Game : public MenuContainer{
private:
    bool shouldExit;
    GraphicsContext *graphics;
    Window *window;
    World *world;
    Resources *res;
    Camera sceneCamera;
    Camera uiCamera;

    void (*update)(Game *, double);

    void (*render)(Game *);

private:
    void mainloop(double dt);

public:
    Game(GraphicsContext *gc, Window *wind, Resources *r, World *w);

    ~Game();

    GraphicsContext *getGraphicsContext();

    Window *getWindow();

    World *getWorld();

    Camera *getSceneCamera();

    Camera *getUICamera();

    void setUpdateFunction(void (*update)(Game *, double));

    void setRenderFunction(void (*render)(Game *));

    void run();

    void stop();
};
}

#endif //GRAE_ENGINE_GAME_H
