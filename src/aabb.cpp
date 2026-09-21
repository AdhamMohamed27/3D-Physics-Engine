#include "aabb.h"
#include <algorithm>
#include <iostream>




IntersectData AABB::IntersectAABB(const AABB& other) const
{
    Vector3f distance1 = other.GetMinCorner() - m_maxCorner;
    Vector3f distance2 = m_minCorner - other.GetMaxCorner();
    Vector3f distance = Vector3f(std::max(distance1.GetX(), distance2.GetX()),
                                 std::max(distance1.GetY(), distance2.GetY()),
                                 std::max(distance1.GetZ(), distance2.GetZ()));
    float maxDistance = std::max(distance.GetX(), std::max(distance.GetY(), distance.GetZ()));
    
    return IntersectData(maxDistance <= 0.0f, maxDistance);

}