#include <origami.hpp>

#include "lib.hpp"

class Game : public Scene
{
public:
    void start(EngineState &state) override
    {
        hello();
    }

    void update(EngineState &state, const Update &time) override
    {
    }

    void destroy(EngineState &state) override {}
};

ENTRY_POINT(Game)