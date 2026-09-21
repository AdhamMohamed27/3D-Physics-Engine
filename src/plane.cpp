#include "plane.h"
#include <cmath>

plane plane::Normalize() const
{
    float length = m_normal.Length();
    if (length <= 1e-6f)
        return *this;
    return plane(m_normal/length, m_distance/length);
}

IntersectData plane::IntersectBoundingSphere(const BoundingSphere& other) const
{
    const float normalLength = m_normal.Length();
    if (normalLength <= 1e-6f)
        return IntersectData(false, 0.0f, Vector3f());

    const Vector3f normal = m_normal / normalLength;
    const float signedDistance = (normal.Dot(other.GetCenter()) + m_distance / normalLength);
    const float surfaceDistance = std::fabs(signedDistance) - other.GetRadius();
    const Vector3f contactNormal = signedDistance >= 0.0f ? normal : normal * -1.0f;
    return IntersectData(surfaceDistance <= 0.0f, surfaceDistance, contactNormal);
}

void plane::transform(const Vector3f& translation)
{
    m_distance -= m_normal.Dot(translation);
}