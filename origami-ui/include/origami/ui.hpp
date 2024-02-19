#pragma once

#include <origami/core.hpp>

class UI : public Resource
{
public:
    void init(EngineState &state) override;

    void _start(EngineState &state);
};