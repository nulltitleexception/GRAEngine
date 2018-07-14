#ifndef GRAE_ENGINE_GEN_H
#define GRAE_ENGINE_GEN_H

#include "resources.h"
#include <string>
#include <fstream>
#include <unordered_map>

/*
 * FORMAT:
 *           key:value
 *           or
 *           key:value{
 *               subkey0:value
 *               subkey1:value
 *               ...
 *           }
 *           or
 *           key{
 *               subkey0:value
 *               subkey1:value
 *               ...
 *           }
*/
namespace GRAE {
class Gen;
namespace PRIVATE {
class Value {
public:
    std::string value;
    std::unique_ptr<Gen> subvalues;
};
}
class Gen {
private:
    std::unordered_map <std::string, PRIVATE::Value> values;
public:
    Gen();

    explicit Gen(Resources *res);

    explicit Gen(std::string s);

    Gen(std::string file, Resources *res, bool &success, std::string &reason);

    std::vector <std::string> getKeys();

    std::string getString(std::string id, std::string fallback = "");

    int getInt(std::string id, int fallback = 0);

    double getDouble(std::string id, double fallback = 0);

    Gen* getSubValues(std::string id);

    int size();

    void removeAll();

    bool load(std::string path);

    void consume(std::string &s);

    std::string toString();
};
}

#endif //GRAE_ENGINE_GEN_H