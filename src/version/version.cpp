#include "version.h"

#include <sstream>

namespace GRAE {
namespace VERSION {
static const int BUILD =

#include "../version"
}

std::string getVersionString() {
    std::ostringstream ret;
    ret << getRelease() << " " << getMajor() << "." << getMinor() << "." << getBuildNumber();
    return ret.str();
}

std::string getRelease() { return VERSION::REL; }

int getMajor() { return VERSION::MAJ; }

int getMinor() { return VERSION::MIN; }

int getBuildNumber() { return VERSION::BUILD; }
}