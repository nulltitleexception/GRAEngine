#include "gen.h"

#include "system/file.h"
#include "system/log.h"

namespace GRAE {
Gen::Gen() {}

Gen::Gen(GRAE::Resources *res) {}

Gen::Gen(std::string s) {
    consume(s);
}

Gen::Gen(File f) {
    if (!f.getExists()) {
        log->err << "file does not exist!";
    }
    std::string contents = f.getContents();
    consume(contents);
}

Gen::Gen(std::string file, Resources *res, bool &success, std::string &reason) {
    success = this->load(file);
}

std::vector<std::string> Gen::getKeys() {
    std::vector<std::string> keys;
    keys.reserve(values.size());
    for (auto const &pair : values) {
        keys.push_back(pair.first);
    }
    return keys;
}

std::string Gen::getString(std::string id, std::string fallback) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        return values.count(id) ? values.at(id).value : fallback;
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).subvalues) ? values.at(key).subvalues->getString(remainder, fallback)
                                                           : fallback;
}

int Gen::getInt(std::string id, int fallback) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        return values.count(id) ? std::stoi(values.at(id).value) : fallback;
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).subvalues) ? values.at(key).subvalues->getInt(remainder, fallback)
                                                           : fallback;
}

double Gen::getDouble(std::string id, double fallback) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        return values.count(id) ? std::stod(values.at(id).value) : fallback;
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).subvalues) ? values.at(key).subvalues->getDouble(remainder, fallback)
                                                           : fallback;
}

bool Gen::getBool(std::string id, bool fallback) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        bool b;
        std::istringstream(values.at(id).value) >> std::boolalpha >> b;
        return values.count(id) ? b : fallback;
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).subvalues) ? values.at(key).subvalues->getBool(remainder, fallback)
                                                           : fallback;
}

Gen *Gen::getSubValues(std::string id) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        return values.count(id) ? values.at(id).subvalues.get() : nullptr;
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).subvalues) ? values.at(key).subvalues->getSubValues(remainder)
                                                           : nullptr;
}

int Gen::size() {
    return values.size();
}

void Gen::removeAll() {
    values.clear();
}

bool Gen::load(std::string path) {
    File file(path);
    if (!file.getExists()) {
        return false;
    }
    std::string contents = file.getContents();
    consume(contents);
    return true;
}

void Gen::consume(std::string &s) {
    while (s.size()) {
        int i = 0;
        while (i < s.size() && s.at(i) == ' ' || s.at(i) == '\t' || s.at(i) == '\n') {
            i++;
        }
        if (i >= s.size()) {
            s = "";
            return;
        }
        int start = i;
        while (i < s.size() && s.at(i) != ':' && s.at(i) != '{' && s.at(i) != '}') {
            i++;
        }
        std::string key = s.substr(start, i - start);
        if (i >= s.size()) {
            s = "";
            if (key.size()) {
                values[key].value = "";
            }
            return;
        } else if (s.at(i) == ':') {
            i++;
            start = i;
            while (i < s.size() && s.at(i) != '\n' && s.at(i) != '{' && s.at(i) != '}') {
                i++;
            }
            std::string val = s.substr(start, i - start);
            if (key.size() || val.size()) {
                values[key].value = val;
            }
        } else {
            if (key.size()) {
                values[key].value = "";
            }
        }
        while (i < s.size() && (s.at(i) == ' ' || s.at(i) == '\t' || s.at(i) == '\n')) {
            i++;
        }
        if (i >= s.size()) {
            s = "";
            return;
        } else if (s.at(i) == '}') {
            s.erase(0, i + 1);
            return;
        } else if (s.at(i) == '{') {
            s.erase(0, i + 1);
            values[key].subvalues = std::make_unique<Gen>();
            values[key].subvalues->consume(s);
        } else {
            s.erase(0, i);
        }
    }
}

std::string Gen::toString() {
    std::stringstream ret;
    for (auto const &pair : values) {
        ret << pair.first << (pair.second.value.size() ? ":" : "") << pair.second.value;
        if (pair.second.subvalues) {
            ret << "{\n" << pair.second.subvalues->toString() << "}";
        }
        ret << "\n";
    }
    return ret.str();
}
}