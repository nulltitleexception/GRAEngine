#ifndef GRAE_ENGINE_EXPRESSION_H
#define GRAE_ENGINE_EXPRESSION_H

#include "environment.h"

#include <string>

namespace GRAE {
class Expression {
private:
    std::string expr;
public:
    Expression(std::string s);

    std::string evaluate(Environment *e);
};
}

#endif //GRAE_ENGINE_EXPRESSION_H
