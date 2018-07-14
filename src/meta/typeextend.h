#include "type.h"

#define ADDTYPE(VAR) \
    TYPES.extend(#VAR, new TypeImpl<VAR>(#VAR), std::type_index(typeid(VAR)));

namespace GRAE {
template<typename T>
class TypeImpl : public Type {
private:
    std::string name;
public:
    TypeImpl(std::string s) : name(s) {}

private:
    struct general_ {
    };
    struct special_ : general_ {
    };
    template<typename>
    struct int_ {
        typedef int type;
    };

    template<typename U, typename int_<decltype(U())>::type = 0>
    void *constructImpl(special_) {
        return new U();
    }

    template<typename U>
    void *constructImpl(general_) {
        log->err << "invalid constructImpl called, returning null";
        return nullptr;
    }

    template<typename U, typename int_<decltype(U(std::declval<Gen*>()))>::type = 0>
    void *constructImpl(Gen* gen, special_) {
        return new U(gen);
    }

    template<typename U>
    void *constructImpl(Gen* gen, general_) {
        log->err << "invalid constructImpl(Gen*) called, fallback to construct()";
        return construct();
    }

    template<typename U, typename int_<decltype(U("", std::declval<Resources *>(),
                                                  std::declval<bool &>(), std::declval<std::string &>()))>::type = 0>
    void *loadImpl(Resources *res, std::string name, special_) {
        return res->get<U>(name);
    }

    template<typename U>
    void *loadImpl(Resources *res, std::string name, general_) {
        log->err << "invalid loadImpl called, returning null";
        return nullptr;
    }

public:
    void *construct() override {
        return constructImpl<T>(special_());
    }

    void *construct(Gen* gen) override {
        return constructImpl<T>(gen, special_());
    }

    void *load(Resources *res, std::string name) override {
        return loadImpl<T>(res, name, special_());
    }

    std::type_index getIndex() override {
        return std::type_index(typeid(T));
    }

    std::string getName() override {
        return name;
    }
};
}