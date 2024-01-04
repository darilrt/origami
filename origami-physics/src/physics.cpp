#include <iostream>

#include "origami/physics.hpp"

void Body::apply_force(Vec3 force)
{
    velocity += force / mass;
}

void Body::apply_impulse(Vec3 impulse)
{
    velocity += impulse / mass;
}

Shared<Body> PhysicWorld::create_body()
{
    auto body = std::make_shared<Body>();
    bodies.push_back(body);
    return body;
}

void PhysicWorld::step(float dt)
{
    for (auto &body : bodies)
    {
    }
}

void PhysicsSystem::init(EngineState &state)
{
}