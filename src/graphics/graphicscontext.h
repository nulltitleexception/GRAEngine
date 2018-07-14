#ifndef GRAE_ENGINE_GRAPHICSCONTEXT_H
#define GRAE_ENGINE_GRAPHICSCONTEXT_H

#include "resource/gen.h"

namespace GRAE {
struct GraphicsProperties {
    int GLMajor;
    int GLMinor;

    GraphicsProperties();

    GraphicsProperties(Gen *gen);
};

class GraphicsContext {
public:
    GraphicsContext();

    GraphicsContext(GraphicsProperties &gp);

    ~GraphicsContext();

    GraphicsProperties &getProperties() {
        return properties;
    }

    void poll();

private:
    bool initialized;
    GraphicsProperties properties;
};
}

#endif //GRAE_ENGINE_GRAPHICSCONTEXT_H
