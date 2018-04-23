#include "config.h"

namespace GRAE {
Config::Config(std::string file, Resources *res) {
    this->load(file);
}

std::string Config::getString(std::string id) {
    return values[id];
}

int Config::getInt(std::string id) {
    return std::stoi(values[id]);
}

double Config::getDouble(std::string id) {
    return std::stod(values[id]);
}

void Config::removeAll() {
    values.clear();
}

bool Config::load(std::string path) {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        std::string key, val;
        for (int i = 0; i < line.length() && key.length() == 0; i++) {
            if (line.at(i) == ':') {
                key = line.substr(0, i);
                val = line.substr(i + 1);
                values[key] = val;
            }
        }
    }
}
}