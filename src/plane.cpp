#include "plane.h"
#include <cmath>

plane plane::Normalize() const
{
    float length = m_normal.Length();
    return plane(m_normal/length, m_distance/length);
}

IntersectData plane::IntersectBoundingSphere(const BoundingSphere& other) const
{
    float distance_from_sphere_center = fabs(m_normal.Dot(other.GetCenter()) + m_distance);
    float distance_from_sphere_surface = fabs(distance_from_sphere_center) - other.GetRaduis();
    return IntersectData(distance_from_sphere_surface <= 0.0f, distance_from_sphere_surface);
}