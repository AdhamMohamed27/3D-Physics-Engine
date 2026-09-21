#ifndef   COLLIDER_INCLUDE_H
#define   COLLIDER_INCLUDE_H
#include "intersect_Data.h"
#include "math3d.h"

class Collider
{
public:
    enum Type {
        SPHERE,
        AABB_SHAPE,
        PLANE
    };

    explicit Collider(const Type type):
    m_type(type) {}

    virtual ~Collider() {}

    IntersectData Intersect(const Collider& other) const;
    virtual void transform(const Vector3f& translation) = 0;
    inline Type GetType() const {return m_type;}
private:
    Type m_type;
};
#endif