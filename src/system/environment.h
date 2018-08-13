#ifndef GRAE_ENGINE_ENVIRONMENT_H
#define GRAE_ENGINE_ENVIRONMENT_H

#include "resource/gen.h"
#include "log.h"
#include "meta/type.h"

#include <string>
#include <sstream>
#include <vector>

namespace GRAE {
namespace PRIVATE {
class Variable {
public:
    virtual ~Variable() = default;

    virtual std::string toString()=0;
};

template<typename T>
class Var : public Variable {
public:
    T val;

    explicit Var(T t) : val{t} {}

    virtual ~Var() {}

    virtual std::string toString() {
        std::ostringstream ret;
        ret << val;
        return ret.str();
    }
};
}
class Environment {
private:
    std::unordered_map<std::string, std::unique_ptr<PRIVATE::Variable>> vars;
    std::unordered_map<std::string, std::vector<std::function<void()>>> callbacks;
public:
    Environment();

    explicit Environment(Gen *gen);

    void registerListener(std::string key, std::function<void()> f);

    void load(Gen *gen, std::string prefix = "");

    template<typename T>
    void set(std::string key, T value) {
        vars[key] = std::unique_ptr<PRIVATE::Variable>(new PRIVATE::Var<T>(value));
        if (callbacks.count(key)) {
            auto vec = callbacks[key];
            callbacks.erase(key);
            for (auto callback : vec) {
                callback();
            }
        }
    }

    template<typename T>
    T get(std::string key) {
        if (vars.count(key)) {
            PRIVATE::Var<T> *ptr = dynamic_cast<PRIVATE::Var<T> *>(vars[key].get());
            if (ptr == nullptr) {

                log->err << "Environment value \"" << key << "\" accessed by wrong type";
                return T();
            } else {
                return ptr->val;
            }
        } else {
            log->err << "Environment value \"" << key << "\" does not exist";
            return T();
        }
    }

    std::string getString(std::string key) {
        if (vars.count(key)) {
            return vars[key]->toString();
        } else {
            log->err << "Environment value \"" << key << "\" does not exist";
            return std::string();
        }
    }

    void bind() { Environment::e = this; }

private:
    static Environment *e;
public:
    static Environment *get() { return Environment::e; };

    static void unbind() { Environment::e = nullptr; }
};
}

#endif //GRAE_ENGINE_ENVIRONMENT_H
