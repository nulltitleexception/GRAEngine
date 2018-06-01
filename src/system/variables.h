#ifndef GRAE_ENGINE_VARIABLES_H
#define GRAE_ENGINE_VARIABLES_H

#include <string>
#include <unordered_map>

namespace GRAE {
namespace PRIVATE {
class Var {
};

template<typename T>
class Variable : public Var {
private:
    T value;
public:
    Variable(T v) {
        value = v;
    }

    T get() {
        return value;
    }

    void set(T v) {
        value = v;
    }
};
}

class VariableSet {
private:
    std::unordered_map<std::string, PRIVATE::Var *> values;
public:
    VariableSet();

    ~VariableSet();

    template<typename T>
    T get(std::string s) {
        return ((PRIVATE::Variable <T> *) values[s])->get();
    }

    template<typename T>
    void set(std::string s, T v) {
        if (values.count(s)) {
            delete values[s];
        }
        values[s] = new PRIVATE::Variable<T>(v);
    }
};
}


#endif //GRAE_ENGINE_VARIABLES_H
