#ifndef GRAE_ENGINE_RESOURCES_H
#define GRAE_ENGINE_RESOURCES_H

#include "system/log.h"
#include "gen.h"
#include "meta/type.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace GRAE {
class Resources;
namespace PRIVATE {
class ResourceHandler {
private:
    std::unordered_map<std::string, void *> resources;
    Type *type;
    std::string directory;
public:
    ResourceHandler(Type *t, std::string dir) : type(t), directory(dir) {}

    ~ResourceHandler() {
        log->debug << "Freeing all <" << type->getName() << ">";
        for (auto pair : resources) {
            type->deconstruct(pair.second);
            log->verbose << pair.first << " unloaded";
        }
    }

    void *&operator[](std::string id) { return resources[id]; }

    bool resourceExists(std::string id) {
        return (bool) resources.count(id);
    }

    std::string getDir() {
        return directory;
    }
};

class DefaultResource {
public:
    virtual ~DefaultResource() = 0;
};

template<typename T>
class DefaultResourceImpl : public DefaultResource {
public:
    T *resource;

    explicit DefaultResourceImpl(Resources *res) : resource(new T(res)) {}

    ~DefaultResourceImpl() {
        delete resource;
        log->verbose << "Default<" << TYPES.get<T>()->getName() << "> unloaded";
    }
};
}
class Resources {
private:
    std::unordered_map<std::type_index, PRIVATE::ResourceHandler *> handlers;
    std::unordered_map<std::type_index, PRIVATE::DefaultResource *> defaults;
    std::string rootDir;
private:
    template<typename T>
    T *const &getDefault() {
        if (!defaults.count(std::type_index(typeid(T)))) {
            log->debug << "Loading default Resource<" << TYPES.get<T>()->getName() << ">";
            defaults[std::type_index(typeid(T))] = new PRIVATE::DefaultResourceImpl<T>(this);
        }
        return ((PRIVATE::DefaultResourceImpl<T> *) defaults[std::type_index(typeid(T))])->resource;
    }

    template<typename T>
    T *getInstanceDefault() {
        return new T(this);
    }

    template<typename T>
    T *const getResource(std::string id) {
        if (!handlers.count(std::type_index(typeid(T)))) {
            log->err << "Resource type not initialized!";
            log->verbose << TYPES.get<T>()->getName();
            return getDefault<T>();
        }
        if (!(handlers[std::type_index(typeid(T))]->resourceExists(id))) {
            log->info << "Loading Resource<" << TYPES.get<T>()->getName() << ">: \"" << id << "\"";
            bool success = false;
            std::string reason = "reason unknown";
            T *resource = new T(id, this, success, reason);
            if (!success) {
                log->err << "Failed to load <" << TYPES.get<T>()->getName() << ">: " << id << " - " << reason;
                delete resource;
                return getDefault<T>();
            } else {
                (*(handlers[std::type_index(typeid(T))]))[id] = resource;
                log->debug << "Successfully Loaded Resource<" << TYPES.get<T>()->getName() << ">: \"" << id << "\"";
            }
        }
        return (T *) (handlers[std::type_index(typeid(T))]->operator[](id));
    }

    template<typename T>
    T *getInstanceResource(std::string id) {
        log->info << "Loading Instance Resource<" << TYPES.get<T>()->getName() << ">: \"" << id << "\"";
        bool success = false;
        std::string reason = "reason unknown";
        T *resource = new T(id, this, success, reason);
        if (!success) {
            log->err << "Failed to load <" << TYPES.get<T>()->getName() << ">: " << id << " - " << reason;
            delete resource;
            return getInstanceDefault<T>();
        } else {
            return resource;
        }
    }

public:
    explicit Resources(std::string root) : rootDir(root) {
        log->info << "Initialized Resources at \"" << rootDir << "\"";
    }

    explicit Resources(Gen *manifest) {
        rootDir = manifest->getString("Resources");
        log->info << "Initialized Resources at \"" << rootDir << "\"";
        Gen *types = manifest->getSubValues("Resources");
        for (std::string key : types->getKeys()) {
            initResourceType(TYPES.get(key), types->getString(key));
        }
    }

    ~Resources() {
        log->info << "Unloading Resources...";
        for (auto pair : handlers) {
            delete pair.second;
        }
        log->info << "Freeing Defaults";
        for (auto pair : defaults) {
            delete pair.second;
        }
        log->info << "All Resources Freed";
    }

    template<typename T>
    void initResourceType(std::string dir) {
        initResourceType(TYPES.get<T>(), dir);
    }

    void initResourceType(Type *type, std::string dir) {
        log->debug << "Initializing Resource Type <" << type->getName() << ">";
        handlers[type->getIndex()] = new PRIVATE::ResourceHandler(type, dir);
    }

    template<typename T>
    T *const get(std::string id = "") {
        if (id.size() > 0) {
            return getResource<T>((rootDir.length() > 0 ? rootDir + "/" : "") +
                                  (((*(handlers[std::type_index(typeid(T))]))).getDir().length() > 0 ?
                                   ((*(handlers[std::type_index(typeid(T))]))).getDir() + "/" : "") + id);
        } else {
            return getDefault<T>();
        }
    }


    template<typename T>
    T *const getFromRoot(std::string id) {
        if (id.size() > 0) {
            return getResource<T>(id);
        } else {
            return getDefault<T>();
        }
    }

    template<typename T>
    T *const getInstance(std::string id = "") {
        if (id.size() > 0) {
            return getInstanceResource<T>((rootDir.length() > 0 ? rootDir + "/" : "") +
                                  (((*(handlers[std::type_index(typeid(T))]))).getDir().length() > 0 ?
                                   ((*(handlers[std::type_index(typeid(T))]))).getDir() + "/" : "") + id);
        } else {
            return getDefault<T>();
        }
    }


    template<typename T>
    T *const getInstanceFromRoot(std::string id) {
        if (id.size() > 0) {
            return getInstanceResource<T>(id);
        } else {
            return getInstanceDefault<T>();
        }
    }
};
}

#endif //GRAE_ENGINE_RESOURCES_H
