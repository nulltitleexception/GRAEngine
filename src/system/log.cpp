#include "log.h"

namespace GRAE {
Log log;
namespace PRIVATE {
std::string levelNames[6] = {
        "None", "Error", "High", "Info", "Debug", "Verbose"
};
}

Log::Log(std::string path, Level l) : level(l), shouldPrint(true), file(path),
                                                                      inner(new PRIVATE::Logs(this)) {}

PRIVATE::Logs *Log::operator->() {
    delete inner;
    inner = new PRIVATE::Logs(this);
    return inner;
}

Log &Log::operator<<(const Level &l) {
    shouldPrint = (l <= level);
    if (shouldPrint) {
        std::cout << std::endl << "<" << PRIVATE::levelNames[static_cast<int>(l)] << ">: ";
    }
    std::stringstream ss;
    ss << std::endl << "<" << PRIVATE::levelNames[static_cast<int>(l)] << ">: ";
    file.append(ss.str());
}

void Log::setFilePath(std::string s) {
    file = File(s);
}

void Log::resetLogFile() {
    file.createOrOverwrite("Log:\n");
}

void Log::setLevel(Level l) {
    level = l;
}

Log::Level Log::getLevel() {
    return level;
}
}