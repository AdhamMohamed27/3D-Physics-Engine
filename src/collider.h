#ifndef   COLLIDER_INCLUDE_H
#define   COLLIDER_INCLUDE_H
#include "intersect_Data.h"
#include "math3d.h"
class Collider
{
public:
    enum{
        SPHERE ,
        AABB ,
        PLANE 
    };
    Collider(int type): 
    m_type(type) {}

    IntersectData Intersect(const Collider& other) const;
    virtual void transform(const Vector3f& translation) ;
    inline int GetType() const {return m_type;}
private:
    int m_type;
};
#endif