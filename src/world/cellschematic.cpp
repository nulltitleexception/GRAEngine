#include "cellschematic.h"

#include "resource/gen.h"
#include "cell.h"

namespace GRAE {
CellSchematic::CellSchematic(Resources *res) {}

CellSchematic::CellSchematic(std::string s, Resources *res, bool &success, std::string &reason){
    Gen *gen = res->getFromRoot<Gen>(s + ".cell");
    std::vector<std::string> keys = gen->getKeys();
    for (auto key : keys) {
        std::string val = gen->getString(key);
        if (key == "Entity") {
            ent.push_back(res->get<EntitySchematic>(val));
        } else {
            log->err << "Invalid object in cell";
        }
    }
    success = true;
}

Cell *CellSchematic::newInstance(){
    return new Cell(this);
}

void CellSchematic::addEntity(EntitySchematic *schematic) {
    ent.push_back(schematic);
}
}