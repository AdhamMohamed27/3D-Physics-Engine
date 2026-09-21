#ifndef AABB_INCLUDE_H
#define AABB_INCLUDE_H
#include "math3d.h"
#include "intersect_Data.h"
#include "collider.h"

class AABB : public Collider
{
public:
    AABB(const Vector3f& minCorner, const Vector3f& maxCorner):
        Collider(Collider::AABB_SHAPE),
        m_minCorner(minCorner),
        m_maxCorner(maxCorner)
    {}

    IntersectData IntersectAABB(const AABB& other) const;
    void transform(const Vector3f& translation);

    inline const Vector3f & GetMinCorner() const {return m_minCorner;}
    inline const Vector3f & GetMaxCorner() const {return m_maxCorner;}
    inline Vector3f GetCenter() const {return (m_minCorner + m_maxCorner) * 0.5f;}

private:
    Vector3f m_minCorner;
    Vector3f m_maxCorner;
};

#endif
