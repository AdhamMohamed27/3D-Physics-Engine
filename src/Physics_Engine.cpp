#include "Physics_Engine.h"
#include <algorithm>

void PhysicsEngine::AddPhysicsObject(std::unique_ptr<PhysicsObject> object)
{
    if (object)
        m_physicsObjects.push_back(std::move(object));
}

void PhysicsEngine::HandleCollisions()
{
    for (std::size_t i = 0; i < m_physicsObjects.size(); ++i)
    {
        for (std::size_t j = i + 1; j < m_physicsObjects.size(); ++j)
        {
            PhysicsObject& first = *m_physicsObjects[i];
            PhysicsObject& second = *m_physicsObjects[j];
            const IntersectData contact = first.GetCollider().Intersect(second.GetCollider());
            if (!contact.getDoesIntersect())
                continue;

            const Vector3f normal = contact.GetNormal();
            const float inverseMass = first.GetInverseMass() + second.GetInverseMass();
            if (inverseMass == 0.0f)
                continue;

            const float velocityAlongNormal = (second.GetVelocity() - first.GetVelocity()).Dot(normal);
            if (velocityAlongNormal < 0.0f)
            {
                const float restitution = std::min(first.GetRestitution(), second.GetRestitution());
                const float impulseMagnitude = -(1.0f + restitution) * velocityAlongNormal / inverseMass;
                const Vector3f impulse = normal * impulseMagnitude;
                first.ApplyImpulse(impulse * -1.0f);
                second.ApplyImpulse(impulse);
            }

            const float correctionMagnitude = contact.GetPenetrationDepth() / inverseMass * 0.8f;
            const Vector3f correction = normal * correctionMagnitude;
            first.Translate(correction * -first.GetInverseMass());
            second.Translate(correction * second.GetInverseMass());
        }
    }
}

void PhysicsEngine::Simulate(float deltaTime)
{
    
    for (const std::unique_ptr<PhysicsObject>& object : m_physicsObjects)
        object->Integrate(deltaTime);

    HandleCollisions();
}
