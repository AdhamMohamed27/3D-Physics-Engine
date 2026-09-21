#ifndef INTERSECT_DATA_H
#define INTERSECT_DATA_H

class IntersectData
{
public:
    IntersectData(const bool doesIntersect, const float disance):
        m_doesIntersect(doesIntersect),
        m_distance(disance)
    {}
    inline bool getDoesIntersect() const {return m_doesIntersect;}
    inline float getDistance() const {return m_distance;}
private:
    const bool m_doesIntersect;
    const float m_distance;

};

#endif