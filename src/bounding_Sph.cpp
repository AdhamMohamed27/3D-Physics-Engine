#include "bounding_Sph.h"
#include "collider.h"

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other)
{
    float radiusDist = m_radius + other.m_radius;
    float centerDist = (other.GetCenter() - m_center).Length();
    float distance = centerDist - radiusDist;

    return IntersectData(distance <= radiusDist, distance);
}

void TransformBoundingSphere::transform(const Vector3f& translation)
{
    m_center += translation;
}
