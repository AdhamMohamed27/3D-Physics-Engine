#include "physics_object.h"

void PhysicsObject::Integrate(float deltaTime)
{
    if (m_inverseMass == 0.0f)
        return;

    Translate(m_velocity * deltaTime);
}

void PhysicsObject::ApplyImpulse(const Vector3f& impulse)
{
    m_velocity += impulse * m_inverseMass;
}

void PhysicsObject::Translate(const Vector3f& translation)
{
    m_position += translation;
    m_collider->transform(translation);
}