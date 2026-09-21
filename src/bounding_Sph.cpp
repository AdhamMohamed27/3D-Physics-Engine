#include "bounding_Sph.h"

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other) const
{
    float radiusDist = m_radius + other.m_radius;
    Vector3f offset = other.GetCenter() - m_center;
    float centerDist = offset.Length();
    float distance = centerDist - radiusDist;
    Vector3f normal = centerDist > 1e-6f ? offset / centerDist : Vector3f(1.0f, 0.0f, 0.0f);

    return IntersectData(distance <= 0.0f, distance, normal);
}

void BoundingSphere::transform(const Vector3f& translation)
{
    m_center += translation;
}
