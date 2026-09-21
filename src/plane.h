#ifndef PLANE_INCLUDE_H
#define PLANE_INCLUDE_H
#include "math3d.h"
#include "intersect_Data.h"
#include "bounding_Sph.h"

class plane
{
    public:
        plane(const Vector3f& normal, float distance):
            m_normal(normal),
            m_distance(distance)
        {}
        plane Normalize() const; 
        IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

        inline const Vector3f & GetNormal() const {return m_normal;}
        inline float GetDistance() const {return m_distance;}
    private:
        const Vector3f m_normal;
        const float m_distance;
};

#endif 