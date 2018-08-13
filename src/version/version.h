#ifndef GRAE_ENGINE_VERSION_H
#define GRAE_ENGINE_VERSION_H

#include <string>

namespace GRAE {
std::string getVersionString();

void setVersionEnvironmentValues();

std::string getRelease();

int getMajor();

int getMinor();

int getBuildNumber();
}

#endif //GRAE_ENGINE_VERSION_H
