#ifndef AABB_INCLUDE_H
#define AABB_INCLUDE_H
#include "math3d.h"
#include "intersect_Data.h"

class AABB
{
public:
    AABB(const Vector3f& minCorner, const Vector3f& maxCorner):
        m_minCorner(minCorner),
        m_maxCorner(maxCorner)
    {}

    IntersectData IntersectAABB(const AABB& other) const;

    inline const Vector3f & GetMinCorner() const {return m_minCorner;}
    inline const Vector3f & GetMaxCorner() const {return m_maxCorner;}

private:
    const Vector3f m_minCorner;
    const Vector3f m_maxCorner;
};

#endif
