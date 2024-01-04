#pragma once

#include <origami/core.hpp>
#include <origami/math.hpp>
#include <vector>

class Body
{
public:
    Vec3 position;
    Vec3 velocity;
    float mass = 1.0f;
    float drag = 0.0f;
    float restitution = 0.0f;
    bool is_static = false;
    bool is_trigger = false;

    void apply_force(Vec3 force);

    void apply_impulse(Vec3 impulse);
};

class PhysicWorld
{
public:
    std::vector<Shared<Body>> bodies;

    Shared<Body> create_body();

    void step(float dt);
};

class PhysicsSystem : public Resource
{
public:
    void init(EngineState &state) override;
};