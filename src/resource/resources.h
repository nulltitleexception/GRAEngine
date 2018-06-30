#ifndef GRAE_ENGINE_RESOURCES_H
#define GRAE_ENGINE_RESOURCES_H

#include "system/log.h"

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <vector>

namespace GRAE {
namespace PRIVATE {
template<typename T>
std::string getTypename() {
    return typeid(T).name();
}

class ResourceHandler {
};

template<typename T>
class Handler : public ResourceHandler {
private:
    std::unordered_map<std::string, T *> resources;
    std::string directory;
public:
    Handler(std::string dir) : directory(dir) {}

    virtual ~Handler() {
        log->debug << "Freeing all <" << PRIVATE::getTypename<T>() << ">";
        for (auto pair : resources) {
            delete pair.second;
        }
    }

    virtual T *&operator[](std::string id) { return resources[id]; }

    virtual bool resourceExists(std::string id) {
        return resources.find(id) != resources.end();
    }

    virtual std::string getDir() {
        return directory;
    }
};
}
class Resources {
private:
    std::unordered_map<std::type_index, PRIVATE::ResourceHandler *> handlers;
    std::string rootDir;
private:
    template<typename T>
    T *const &getResource(std::string id) {
        log->verbose << "Resource<" << PRIVATE::getTypename<T>() << "> Requested: \"" << id << "\"";
        if (!((PRIVATE::Handler<T> *) (handlers[std::type_index(typeid(T))]))->resourceExists(id)) {
            log->info << "Loading Resource<" << PRIVATE::getTypename<T>() << ">: \"" << id << "\"";
            bool success = false;
            std::string reason = "";
            ((*(PRIVATE::Handler<T> *) (handlers[std::type_index(typeid(T))])))[id] = new T(id, this, success, reason);
            if (!success) {
                log->err << "Failed to load <" << PRIVATE::getTypename<T>() << ">: " << id << " - " << reason;
            } else {
                log->debug << "Successfully Loaded Resource<" << PRIVATE::getTypename<T>() << ">: \"" << id << "\"";
            }
        }
        return ((*(PRIVATE::Handler<T> *) (handlers[std::type_index(typeid(T))])))[id];
    }

public:
    Resources(std::string root) : rootDir(root) {
        log->info << "Initialized Resources at \"" << root << "\"";
    }

    ~Resources() {
        for (auto pair : handlers) {
            delete pair.second;
        }
    }

    template<typename T>
    void initResourceType(std::string dir) {
        log->debug << "Initializing Resource Type <" << PRIVATE::getTypename<T>() << ">";
        handlers[std::type_index(typeid(T))] = new PRIVATE::Handler<T *>(dir);
    }

    template<typename T>
    T *const &get(std::string id) {
        return getResource<T>((rootDir.length() > 0 ? rootDir + "/" : "") +
                              (((*(PRIVATE::Handler<T> *) (handlers[std::type_index(typeid(T))]))).getDir().length() > 0
                               ? ((*(PRIVATE::Handler<T> *) (handlers[std::type_index(typeid(T))]))).getDir() + "/"
                               : "") + id);
    }


    template<typename T>
    T *const &getFromRoot(std::string id) {
        return getResource<T>(id);
    }
};
}

#endif //GRAE_ENGINE_RESOURCES_H
