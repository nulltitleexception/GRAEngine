#include "cell.h"

namespace GRAE {
Cell::Cell() {

}

Cell::Cell(std::string path, Resources *res, bool& success, std::string& reason) {

}

Cell::~Cell() {
    for (int i = 0; i < entities.size(); i++) {
        delete entities[i];
    }
}

void Cell::update(double dt) {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(dt);
    }
}

void Cell::render() {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->render();
    }
}
}