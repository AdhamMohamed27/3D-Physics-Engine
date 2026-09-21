#include "collider.h"
#include "bounding_Sph.h"
#include <iostream>
#include <cstdlib>

IntersectData Collider::Intersect(const Collider& other) const
{
    if(m_type == SPHERE && other.GetType() == SPHERE)
    {
        BoundingSphere* sphere1 = (BoundingSphere*)this;
        return sphere1-> IntersectBoundingSphere(*(BoundingSphere*)&other);
    }
    std::cerr << "Collider::Intersect: Unsupported collider types for intersection test." << std::endl;
    std::exit(EXIT_FAILURE);

    return IntersectData(false, 0.0f); // This line will never be reached, but is here to satisfy the compiler.
}