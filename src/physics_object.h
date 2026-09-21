#ifndef PHYSICS_OBJECT_INCLUDE_H
#define PHYSICS_OBJECT_INCLUDE_H
#include "math3d.h"
#include "bounding_Sph.h"
#include <memory>

class PhysicsObject
{
public:
    PhysicsObject(const Vector3f& position, const Vector3f& velocity, float radius,
                  float mass = 1.0f, float restitution = 0.5f):
        m_position(position),
        m_velocity(velocity),
        m_collider(new BoundingSphere(position, radius)),
        m_inverseMass(mass > 0.0f ? 1.0f / mass : 0.0f),
        m_restitution(Clamp(restitution, 0.0f, 1.0f))
    {}

    PhysicsObject(std::unique_ptr<Collider> collider, const Vector3f& velocity,
                  float mass = 1.0f, float restitution = 0.5f):
        m_position(),
        m_velocity(velocity),
        m_collider(std::move(collider)),
        m_inverseMass(mass > 0.0f ? 1.0f / mass : 0.0f),
        m_restitution(Clamp(restitution, 0.0f, 1.0f))
    {}

    PhysicsObject(const PhysicsObject&) = delete;
    PhysicsObject& operator=(const PhysicsObject&) = delete;
    PhysicsObject(PhysicsObject&&) = default;
    PhysicsObject& operator=(PhysicsObject&&) = default;

    void Integrate(float deltaTime);

    inline const Vector3f & GetPosition() const {return m_position;}
    inline const Vector3f & GetVelocity() const {return m_velocity;}
    inline Collider& GetCollider() {return *m_collider;}
    inline const Collider& GetCollider() const {return *m_collider;}
    inline float GetInverseMass() const {return m_inverseMass;}
    inline float GetRestitution() const {return m_restitution;}
    inline void setVelocity(const Vector3f& velocity) {m_velocity = velocity;}
    void ApplyImpulse(const Vector3f& impulse);
    void Translate(const Vector3f& translation);
private:
    Vector3f m_position;
    Vector3f m_velocity;
    std::unique_ptr<Collider> m_collider;
    float m_inverseMass;
    float m_restitution;
};

#endif