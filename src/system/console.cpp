#include "console.h"

#include "expression.h"

namespace GRAE {
Console::Console(Environment *e) {
    environment = e;
}

Console::~Console() {}

void Console::addLine(std::string s) {
    lines.push_back(s);
}

void Console::execute(std::string s) {
    addLine(s);
    Expression e(s);
    e.evaluate(environment);
}
}