#ifndef GRAE_ENGINE_FILE_H
#define GRAE_ENGINE_FILE_H

#include <fstream>
#include <vector>
#include <sstream>
#include <string>

namespace GRAE {
class File {
private:
    std::string myPath;
public:
    File(std::string path);

    std::vector<std::string> getLines();

    std::string getContents();

    char *getBytes();

    void createOrOverwrite(const char *contents, long size);

    void createOrOverwrite(std::string contents);

    void append(const char *contents, long size);

    void append(std::string contents);

    bool getExists();
};
}

#endif //GRAE_ENGINE_FILE_H
