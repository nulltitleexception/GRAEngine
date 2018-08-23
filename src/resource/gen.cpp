#include "gen.h"

#include "system/file.h"
#include "system/log.h"
#include <algorithm>

void strReplace(std::string &s, std::string before, std::string after) {
    int pos;
    while ((pos = s.find(before)) != std::string::npos) {
        s.replace(pos, before.length(), after);
    }
}

void strEscape(std::string &s) {
    strReplace(s, "\\\\", "|||BACKSLASH|||");
    strReplace(s, "\\n", "\n");
    strReplace(s, "\\s", " ");
    strReplace(s, "\\t", "\t");
    strReplace(s, "|||BACKSLASH|||", "\\");
}

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

bool Gen::getPresent(std::string id) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        return values.count(id) > 0;
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).at(0).subvalues->getPresent(remainder));
}

int Gen::getCount(std::string id) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        return values.count(id) > 0 ? values.at(id).size() : 0;
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return values.count(key) ? values.at(key).at(0).subvalues->getCount(remainder) : 0;
}

std::string Gen::getFirstString(std::string id, std::string fallback) { return getString(id, 0, fallback); }

int Gen::getFirstInt(std::string id, int fallback) { return getInt(id, 0, fallback); }

double Gen::getFirstDouble(std::string id, double fallback) { return getDouble(id, 0, fallback); }

bool Gen::getFirstBool(std::string id, bool fallback) { return getBool(id, 0, fallback); }

std::string Gen::getString(std::string id, int index, std::string fallback) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        return values.count(id) ? values.at(id).at(index).value : fallback;
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).at(index).subvalues) ? values.at(key).at(index).subvalues->getString(
            remainder, 0, fallback) : fallback;
}

int Gen::getInt(std::string id, int index, int fallback) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        try {
            return values.count(id) ? std::stoi(values.at(id).at(index).value) : fallback;
        } catch (...) {
            return fallback;
        }
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).at(index).subvalues) ? values.at(key).at(index).subvalues->getInt(
            remainder, 0, fallback) : fallback;
}

double Gen::getDouble(std::string id, int index, double fallback) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        try {
            return values.count(id) ? std::stod(values.at(id).at(index).value) : fallback;
        } catch (...) {
            return fallback;
        }

    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).at(index).subvalues) ? values.at(key).at(index).subvalues->getDouble(
            remainder, 0, fallback) : fallback;
}

bool Gen::getBool(std::string id, int index, bool fallback) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        bool b;
        std::istringstream(values.at(id).at(index).value) >> std::boolalpha >> b;
        return values.count(id) ? b : fallback;
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).at(index).subvalues) ? values.at(key).at(index).subvalues->getBool(
            remainder, 0, fallback) : fallback;
}

Gen *Gen::getSubValues(std::string id, int index) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        return values.count(id) ? values.at(id).at(index).subvalues.get() : nullptr;
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).at(index).subvalues) ? values.at(key).at(index).subvalues->getSubValues(
            remainder, 0) : nullptr;
}

bool Gen::isInt(std::string id, int index) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        try {
            int i = std::stoi(values.at(id).at(index).value);
            return true;
        } catch (...) {
            return false;
        }
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).at(index).subvalues != nullptr &&
            values.at(key).at(index).subvalues->isInt(remainder));
}

bool Gen::isDouble(std::string id, int index) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        try {
            double d = std::stod(values.at(id).at(index).value);
            return true;
        } catch (...) {
            return false;
        }
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).at(index).subvalues != nullptr &&
            values.at(key).at(index).subvalues->isDouble(remainder));
}

bool Gen::isBool(std::string id, int index) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        std::string val = values.at(id).at(index).value;
        std::transform(val.begin(), val.end(), val.begin(), ::tolower);
        return val == "true" || val == "false";
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).at(index).subvalues != nullptr &&
            values.at(key).at(index).subvalues->isBool(remainder));
}

bool Gen::hasSubValues(std::string id, int index) {
    std::string::size_type loc = id.find('.', 0);
    if (loc == std::string::npos) {
        return (values.count(id) && values.at(id).at(index).subvalues.get() != nullptr);
    }
    std::string key = id.substr(0, loc);
    std::string remainder = id.substr(loc + 1);
    return (values.count(key) && values.at(key).at(index).subvalues != nullptr &&
            values.at(key).at(index).subvalues->hasSubValues(remainder));
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
        while (i < s.size() && s.at(i) != ':' && s.at(i) != '{' && s.at(i) != '}' && s.at(i) != '\n') {
            i++;
        }
        std::string key = s.substr(start, i - start);
        if (i >= s.size()) {
            s = "";
            if (key.size()) {
                values[key].push_back(PRIVATE::Value());
            }
            return;
        } else if (s.at(i) == '\n') {
            if (key.size()) {
                values[key].push_back(PRIVATE::Value());
            }
        } else if (s.at(i) == ':') {
            i++;
            while (i < s.size() && (s.at(i) == ' ' || s.at(i) == '\t')) {
                i++;
            }
            start = i;
            while (i < s.size() && s.at(i) != '\n' && s.at(i) != '{' && s.at(i) != '}') {
                i++;
            }
            std::string val = s.substr(start, i - start);
            if (key.size() || val.size()) {
                strEscape(val);
                values[key].push_back(PRIVATE::Value());
                values[key].back().value = val;
            }
        } else {
            if (key.size()) {
                values[key].push_back(PRIVATE::Value());
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
            values[key].back().subvalues = std::make_unique<Gen>();
            values[key].back().subvalues->consume(s);
        } else {
            s.erase(0, i);
        }
    }
}

std::string Gen::toString(std::string prefix) {
    std::stringstream ret;
    for (auto const &pair : values) {
        for (int i = 0; i < pair.second.size(); i++) {
            ret << prefix << pair.first << (pair.second[i].value.size() ? ":" : "") << pair.second[i].value;
            if (pair.second[i].subvalues) {
                ret << "{\n" << pair.second[i].subvalues->toString(prefix + "    ") << "\n" << prefix << "}";
            }
            if (i < pair.second.size() - 1) {
                ret << "\n";
            }
        }
    }
    return ret.str();
}
}