#ifndef PLANE_INCLUDE_H
#define PLANE_INCLUDE_H
#include "math3d.h"
#include "intersect_Data.h"
#include "bounding_Sph.h"
#include "collider.h"

class plane : public Collider
{
    public:
        plane(const Vector3f& normal, float distance):
        Collider(Collider::PLANE),
            m_normal(normal),
            m_distance(distance)
        {}
        plane Normalize() const; 
        IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;
        void transform(const Vector3f& translation);

        inline const Vector3f & GetNormal() const {return m_normal;}
        inline float GetDistance() const {return m_distance;}
    private:
        Vector3f m_normal;
        float m_distance;
};

#endif 