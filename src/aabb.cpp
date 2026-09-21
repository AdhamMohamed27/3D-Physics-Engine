#include "aabb.h"
#include <algorithm>
#include <cmath>

void AABB::transform(const Vector3f& translation)
{
    m_minCorner += translation;
    m_maxCorner += translation;
}

IntersectData AABB::IntersectAABB(const AABB& other) const
{
    Vector3f distance1 = other.GetMinCorner() - m_maxCorner;
    Vector3f distance2 = m_minCorner - other.GetMaxCorner();
    Vector3f distance = Vector3f(std::max(distance1.GetX(), distance2.GetX()),
                                 std::max(distance1.GetY(), distance2.GetY()),
                                 std::max(distance1.GetZ(), distance2.GetZ()));
    float maxDistance = std::max(distance.GetX(), std::max(distance.GetY(), distance.GetZ()));
    
    Vector3f centerDelta = other.GetCenter() - GetCenter();
    Vector3f normal(1.0f, 0.0f, 0.0f);
    float axisDistance = centerDelta.GetX();
    if (std::fabs(centerDelta.GetY()) > std::fabs(axisDistance))
    {
        axisDistance = centerDelta.GetY();
        normal = Vector3f(0.0f, 1.0f, 0.0f);
    }
    if (std::fabs(centerDelta.GetZ()) > std::fabs(axisDistance))
    {
        axisDistance = centerDelta.GetZ();
        normal = Vector3f(0.0f, 0.0f, 1.0f);
    }
    if (maxDistance <= 0.0f)
    {
        const float overlapX = std::min(m_maxCorner.GetX(), other.m_maxCorner.GetX()) - std::max(m_minCorner.GetX(), other.m_minCorner.GetX());
        const float overlapY = std::min(m_maxCorner.GetY(), other.m_maxCorner.GetY()) - std::max(m_minCorner.GetY(), other.m_minCorner.GetY());
        const float overlapZ = std::min(m_maxCorner.GetZ(), other.m_maxCorner.GetZ()) - std::max(m_minCorner.GetZ(), other.m_minCorner.GetZ());
        normal = Vector3f(1.0f, 0.0f, 0.0f);
        if (overlapY < overlapX && overlapY <= overlapZ) normal = Vector3f(0.0f, 1.0f, 0.0f);
        if (overlapZ < overlapX && overlapZ < overlapY) normal = Vector3f(0.0f, 0.0f, 1.0f);
    }
    if (axisDistance < 0.0f)
        normal *= -1.0f;

    return IntersectData(maxDistance <= 0.0f, maxDistance, normal);

}