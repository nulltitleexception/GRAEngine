#ifndef GRAE_ENGINE_VARTEXT_H
#define GRAE_ENGINE_VARTEXT_H

#include "text.h"
#include "system/environment.h"

namespace GRAE {
class VarText : Text {
private:
    std::string raw;
public:
    VarText(Resources *res, Gen *gen) : Text(res, gen) {
        raw = string;
        refresh();
    }

    virtual ~VarText() {
    }

    virtual void setString(std::string s) {
        raw = s;
        refresh();
    }

    virtual void refresh() {
        std::string formatted = raw;
        int pos;
        while ((pos = formatted.find("$[")) != std::string::npos) {
            int posEnd = formatted.find("]", pos);
            Environment::get()->registerListener(formatted.substr(pos + 2, posEnd - pos - 2),
                                                 [&]() { this->refresh(); });
            formatted.replace(pos, (posEnd - pos) + 1,
                              Environment::get()->getString(formatted.substr(pos + 2, posEnd - pos - 2)));
        }
        Text::setString(formatted);
    }
};
}

#endif //GRAE_ENGINE_VARTEXT_H
