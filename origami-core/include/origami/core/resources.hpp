#pragma once

class EngineState;

class Resource
{
public:
    virtual void init(EngineState &state) = 0;
};
