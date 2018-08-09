#include "cast.h"

#include "engine.h"

#include "typelist"

#define MAKE_CAST_MAP(VAR) \
    indexedCasts[std::type_index(typeid(VAR))] = &cast_impl<VAR, F>;

#define MAKE_CASTER_MAP(FROM) \
        indexedCasters[std::type_index(typeid(FROM))] = std::unique_ptr<InnerCaster>((InnerCaster*)(new InnerCasterImpl<FROM>()));

namespace GRAE {
typedef void *(*castPtr)(void *);

template<typename T, typename F>
void *cast_impl(void *p) { return ((T *) ((F *) p)); }

template<typename F>
class InnerCasterImpl {
private:
    std::unordered_map<std::type_index, castPtr> indexedCasts;
public:
    InnerCasterImpl() {
        TYPELIST(MAKE_CAST_MAP)
    }

    virtual ~InnerCasterImpl() {}

    virtual void *cast(std::type_index to, void *p) {
        castPtr call = indexedCasts[to];
        return (*call)(p);
    }
};

TypeCaster::TypeCaster() {
    TYPELIST(MAKE_CASTER_MAP)
}

void *TypeCaster::cast(std::type_index to, std::type_index from, void *p) {
    InnerCaster *caster = indexedCasters[from].get();
    return caster->cast(to, p);
}

TypeCaster CAST;
}