#ifndef PHYSICS_ENGINE_INCLUDE_H
#define PHYSICS_ENGINE_INCLUDE_H
#include "physics_object.h"
#include <cstddef>
#include <memory>
#include <vector>

class PhysicsEngine
{
public:
    explicit PhysicsEngine(std::size_t expectedObjectCount = 64)
    {
        m_physicsObjects.reserve(expectedObjectCount);
    }
    void AddPhysicsObject(std::unique_ptr<PhysicsObject> object);
    void HandleCollisions();
    void handleCollisions() { HandleCollisions(); }
    void Simulate(float deltaTime);

private:
    std::vector<std::unique_ptr<PhysicsObject>> m_physicsObjects;
};

#endif // PHYSICS_ENGINE_INCLUDE_H
