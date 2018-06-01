#ifndef GRAE_ENGINE_RESOURCES_H
#define GRAE_ENGINE_RESOURCES_H

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace GRAE {
class File {
private:
    std::string myPath;
public:
    File(std::string path) : myPath(path) {}

    std::vector<std::string> getLines() {
        std::ifstream in;
        in.open(myPath);
        std::vector<std::string> lines;
        std::string line;
        if (in.good()) {
            while (std::getline(in, line)) {
                lines.push_back(line);
            }
        } else {
            std::cout << "File could not be read: " << myPath << std::endl;
        }
        in.close();
        return lines;
    }

    std::string getContents() {
        std::ifstream in;
        in.open(myPath);
        std::ostringstream contents;
        if (in.good()) {
            contents << in.rdbuf();
        } else {
            std::cout << "File could not be read: " << myPath << std::endl;
        }
        in.close();
        return contents.str();
    }

    char* getBytes(){
        std::ifstream in(myPath, std::ios::binary | std::ios::ate);
        long length = in.tellg();
        in.seekg(0, in.beg);
        char* contents = new char[length];
        in.read(contents, length);
        return contents;
    }

    void createOrOverwrite(char* contents, long size){
        std::ofstream out(myPath, std::ios::out | std::ios::binary);
        out.write(contents, size);
    }

    bool getExists(){
        std::ifstream in(myPath);
        return in.good();
    }
};
namespace PRIVATE {
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
public:
    Resources(std::string root) : rootDir(root) {}

    ~Resources(){
        for (auto pair : handlers) {
            delete pair.second;
        }
    }

    template<typename T>
    void initResourceType(std::string dir) {
        handlers[std::type_index(typeid(T))] = new PRIVATE::Handler<T *>(dir);
    }

    template<typename T>
    T *const &get(std::string id) {
        if (!((PRIVATE::Handler<T> *) (handlers[std::type_index(typeid(T))]))->resourceExists(id)) {
            ((*(PRIVATE::Handler<T> *) (handlers[std::type_index(typeid(T))])))[id] = new T(
                    (rootDir.length() > 0 ? rootDir + "/" : "") +
                    (((*(PRIVATE::Handler<T> *) (handlers[std::type_index(typeid(T))]))).getDir().length() > 0 ?
                     ((*(PRIVATE::Handler<T> *) (handlers[std::type_index(typeid(T))]))).getDir() + "/" : "") +
                    id, this);
        }
        return ((*(PRIVATE::Handler<T> *) (handlers[std::type_index(typeid(T))])))[id];
    }
};
}

#endif //GRAE_ENGINE_RESOURCES_H
