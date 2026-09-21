#ifndef INTERSECT_DATA_H
#define INTERSECT_DATA_H

#include "math3d.h"

class IntersectData
{
public:
    IntersectData(const bool doesIntersect, const float distance,
                  const Vector3f& normal = Vector3f()):
        m_doesIntersect(doesIntersect),
        m_distance(distance),
        m_normal(normal)
    {}
    inline bool getDoesIntersect() const {return m_doesIntersect;}
    inline float getDistance() const {return m_distance;}
    inline float GetPenetrationDepth() const {return m_distance < 0.0f ? -m_distance : 0.0f;}
    inline const Vector3f& GetNormal() const {return m_normal;}
private:
    const bool m_doesIntersect;
    const float m_distance;
    const Vector3f m_normal;

};

#endif