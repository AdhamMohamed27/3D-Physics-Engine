#ifndef PHYSICS_ENGINE_INCLUDE_H
#define PHYSICS_ENGINE_INCLUDE_H
#include "physics_object.h"
#include <vector>

class PhysicsEngine
{
public:
    PhysicsEngine() {}
    void AddPhysicsObject(const PhysicsObject& object);
    void handleCollisions();
    void Simulate(float deltaTime);

private:
    std::vector<PhysicsObject> m_physicsObjects;
};

#endif // PHYSICS_ENGINE_INCLUDE_H
