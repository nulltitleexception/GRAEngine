#ifndef GRAE_ENGINE_LOG_H
#define GRAE_ENGINE_LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

namespace GRAE {
namespace PRIVATE {
extern std::string levelNames[6];
struct Logs;
}
class Log {
public:
    enum class Level {
        None = 0,
        Error = 1,
        High = 2,
        Info = 3,
        Debug = 4,
        Verbose = 5,
    };
private:
    Level level;
    bool shouldPrint;
    std::string path;
    std::ofstream file;
    PRIVATE::Logs* inner;
public:
    Log(std::string p = "log", Level l = Level::Info);

    ~Log();

    PRIVATE::Logs *operator->();

    template<typename T>
    Log &operator<<(const T &t) {
        if (shouldPrint) {
            std::cout << t;
        }
        file << t;
    }

    Log &operator<<(const Level &l);

    void setFilePath(std::string s);

    void resetLogFile();

    void setLevel(Level l);

    Level getLevel();
};
namespace PRIVATE {
struct subLog {
    bool addLevel;
    Log::Level level;
    Log *log;

    subLog(Log *l, Log::Level lev) : level(lev), log(l) {
        addLevel = true;
    }

    template<typename T>
    subLog &operator<<(const T &t) {
        if (addLevel) {
            (*log) << level;
            addLevel = false;
        }
        (*log) << t;
        return *this;
    }
};

struct Logs {
    subLog err;
    subLog high;
    subLog info;
    subLog debug;
    subLog verbose;

    Logs(Log *l) : err(l, Log::Level::Error), high(l, Log::Level::High), info(l, Log::Level::Info),
                   debug(l, Log::Level::Debug), verbose(l, Log::Level::Verbose) {}
};
}
extern Log log;
}

#endif //GRAE_ENGINE_LOG_H
