#include "log.h"

namespace GRAE {
Log log;
namespace PRIVATE {
std::string levelNames[6] = {
        "None", "Error", "High", "Info", "Debug", "Verbose"
};
}

Log::Log(std::string p, Level l) : level(l), shouldPrint(true), path(p), file(p, std::ios::out | std::ios::app),
                                      inner(new PRIVATE::Logs(this)) {}

Log::~Log() {
    file << std::flush;
    std::cout << std::flush;
    file.close();
    delete inner;
}

PRIVATE::Logs *Log::operator->() {
    delete inner;
    inner = new PRIVATE::Logs(this);
    return inner;
}

Log &Log::operator<<(const Level &l) {
    shouldPrint = (l <= level);
    if (shouldPrint) {
        std::cout << "\n" << "<" << PRIVATE::levelNames[static_cast<int>(l)] << ">: ";
    }
    file << "\n<" << PRIVATE::levelNames[static_cast<int>(l)] << ">: ";
}

void Log::setFilePath(std::string s) {
    path = s;
    file.close();
    file.open(s, std::ios::out | std::ios::app);
}

void Log::resetLogFile() {
    file.close();
    file.open(path, std::ofstream::out | std::ofstream::trunc);
}

void Log::setLevel(Level l) {
    level = l;
}

Log::Level Log::getLevel() {
    return level;
}
}