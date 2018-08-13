#include "version.h"

#include "system/environment.h"

#include <sstream>

namespace GRAE {
namespace VERSION {
static const int BUILD =

#include "../version"

}

std::string getVersionString() {
    std::ostringstream ret;
    ret << getRelease() << " " << getMajor() << "." << getMinor() << " B" << getBuildNumber();
    return ret.str();
}

void setVersionEnvironmentValues() {
    Environment::get()->set("VERSION", getVersionString());
    Environment::get()->set("VERSION.RELEASE", getRelease());
    Environment::get()->set("VERSION.MAJOR", getMajor());
    Environment::get()->set("VERSION.MINOR", getMinor());
    Environment::get()->set("VERSION.BUILD", getBuildNumber());
}

std::string getRelease() { return VERSION::REL; }

int getMajor() { return VERSION::MAJ; }

int getMinor() { return VERSION::MIN; }

int getBuildNumber() { return VERSION::BUILD; }

}