#ifndef BOUNDING_SPH_H
#define BOUNDING_SPH_H
#include "math3d.h"
#include "intersect_Data.h"
#include "collider.h"

class BoundingSphere : public Collider
{
    public:
        BoundingSphere(const Vector3f& center, float radius):
            Collider(Collider::SPHERE),
            m_center(center),
            m_radius(radius)
        {}

        IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;
        void transform(const Vector3f& translation);
        inline const Vector3f & GetCenter() const {return m_center;}
        inline float GetRadius() const {return m_radius;}
        inline float GetRaduis() const {return GetRadius();}
    private:
        Vector3f m_center;
        const float m_radius;
};

#endif // BOUNDING_SPH_H