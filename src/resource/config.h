#ifndef GRAE_ENGINE_CONFIG_H
#define GRAE_ENGINE_CONFIG_H

#include "Resources.h"
#include <string>
#include <fstream>
#include <unordered_map>

/*
 * FORMAT:  each line should be "key:value"
 * if there is whitespace, it is included in the respective part.
*/
namespace GRAE {
class Config {
private:
    std::unordered_map<std::string, std::string> values;
public:
    Config(std::string file, Resources* res);

    std::string getString(std::string id);

    int getInt(std::string id);

    double getDouble(std::string id);

    void removeAll();

    bool load(std::string path);
};
}

#endif //GRAE_ENGINE_CONFIG_H