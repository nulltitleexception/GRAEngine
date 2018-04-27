#ifndef GRAE_ENGINE_VERSION_H
#define GRAE_ENGINE_VERSION_H

#include <string>
#include <sstream>

std::string getVersionString(){
    int BUILD_NUMBER =
#include "../version"
    std::ostringstream ret;
    ret << BUILD << " " << MAJ << "." << MIN << "." << BUILD_NUMBER;
    return ret.str();
}

#endif //GRAE_ENGINE_VERSION_H
