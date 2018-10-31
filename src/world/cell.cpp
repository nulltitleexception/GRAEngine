#include "cell.h"

namespace GRAE {
Cell::Cell(Resources *res) {}

Cell::Cell(std::string s, Resources *res, bool &success, std::string &reason) {
    Gen *gen = res->getFromRoot<Gen>(s + ".cell");
    std::vector<std::string> keys = gen->getKeys();
    for (auto key : keys) {
        if (key == "Entity") {
            for (int i = 0; i < gen->getCount(key); i++) {
                std::string val = gen->getString(key, i);
                entities.push_back(res->get<EntitySchematic>(val)->newInstance(this));
            }
        } else {
            log->debug << "Unknown object in cell";
        }
    }
    success = true;
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

TerrainCell::TerrainCell(Resources *res) : Cell(nullptr), width(0), height(0) {

}


TerrainCell::TerrainCell(std::string s, Resources *res, bool &success, std::string &reason) : Cell(s, res, success,
                                                                                                   reason) {
}

TerrainCell::~TerrainCell() {
    for (int i = 0; i < entities.size(); i++) {
        delete entities[i];
    }
}

void TerrainCell::update(double dt) {
    for (int i = 0; i < entities.size(); i++) {
        //check for terrtain collisions;
        entities[i]->update(dt);
    }
}

void TerrainCell::render() {
    Cell::render();
    if (mesh.get() != nullptr) {
        mesh->render();
    }
}
}