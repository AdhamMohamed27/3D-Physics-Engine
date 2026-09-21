#include "physics_object.h"

void PhysicsObject::Integrate(float deltaTime)
{
    m_position += m_velocity * deltaTime;
}