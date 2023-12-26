#include "origami/state.hpp"

void EngineState::start()
{
    for (auto &resource : resources)
    {
        resource.second->init(*this);
    }
}