#include "game.h"

#include "system/log.h"

#include "engine.h"

namespace GRAE {
void Game::mainloop(double dt) {
    //update
    update(this, dt);
    world->update(dt);
    //clear buffer
    window->clear();
    //draw scene
    sceneCamera.bind();
    render(this);
    world->render();
    //clear depth buffer, UI overrides scene
    window->clear(false, true);
    //draw ui
    uiCamera.bind();
    renderChildren();
    //swap and poll
    window->swap();
    graphics->poll();
}

Game::Game(GraphicsContext *gc, Window *wind, Resources *r, World *w) : shouldExit(false), graphics(gc), window(wind),
                                                                        res(r), world(w) {
    world->game = this;
}

Game::~Game() {

}

GraphicsContext *Game::getGraphicsContext() {
    return graphics;
}

Window *Game::getWindow() {
    return window;
}

World *Game::getWorld() {
    return world;
}

Camera *Game::getSceneCamera() {
    return &sceneCamera;
}

Camera *Game::getUICamera() {
    return &uiCamera;
}

void Game::setUpdateFunction(void (*f)(Game *, double)) {
    update = f;
}

void Game::setRenderFunction(void (*f)(Game *)) {
    render = f;
}

void Game::run() {
    log->verbose << "Game running";
    double frameTime = System::getTime();
    double fpsTime = frameTime;
    double dt = 0;
    int fpsCount = 0;
    int fps = 0;
    int frames = 0;
    while (!shouldExit && !window->closeRequested()) {
        mainloop(dt);
        fpsCount++;
        frames++;
        if (frameTime - fpsTime >= 1) {
            fpsTime = frameTime;
            fps = fpsCount;
            fpsCount = 0;
        }
        double temptime = System::getTime();
        dt = temptime - frameTime;
        frameTime = temptime;
    }
}

void Game::stop() {
    shouldExit = true;
}

double Game::getSizeX() {
    return window->getProperties().width;
}

double Game::getSizeY() {
    return window->getProperties().height;
}
}