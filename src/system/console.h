#ifndef GRAE_ENGINE_CONSOLE_H
#define GRAE_ENGINE_CONSOLE_H

#include "environment.h"

#include <string>
#include <vector>

namespace GRAE {
class Console {
private:
    Environment *environment;
    std::vector<std::string> lines;
public:
    Console(Environment *e);

    ~Console();

    void addLine(std::string);

    void execute(std::string);
};
}

#endif //GRAE_ENGINE_CONSOLE_H
