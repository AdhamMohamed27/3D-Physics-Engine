#include "collider.h"
#include "bounding_Sph.h"
#include "aabb.h"
#include "plane.h"
#include <algorithm>
#include <cmath>

namespace
{
IntersectData IntersectSphereAABB(const BoundingSphere& sphere, const AABB& box)
{
    const Vector3f closest(
        Clamp(sphere.GetCenter().GetX(), box.GetMinCorner().GetX(), box.GetMaxCorner().GetX()),
        Clamp(sphere.GetCenter().GetY(), box.GetMinCorner().GetY(), box.GetMaxCorner().GetY()),
        Clamp(sphere.GetCenter().GetZ(), box.GetMinCorner().GetZ(), box.GetMaxCorner().GetZ()));
    const Vector3f offset = closest - sphere.GetCenter();
    const float distance = offset.Length();

    if (distance > 1e-6f)
    {
        const Vector3f normal = offset / distance;
        const float surfaceDistance = distance - sphere.GetRadius();
        return IntersectData(surfaceDistance <= 0.0f, surfaceDistance, normal);
    }

    const Vector3f center = box.GetCenter();
    const Vector3f local = sphere.GetCenter() - center;
    const Vector3f halfSize = (box.GetMaxCorner() - box.GetMinCorner()) * 0.5f;
    const float distances[3] = {
        halfSize.GetX() - std::fabs(local.GetX()),
        halfSize.GetY() - std::fabs(local.GetY()),
        halfSize.GetZ() - std::fabs(local.GetZ())};
    int axis = 0;
    if (distances[1] < distances[axis]) axis = 1;
    if (distances[2] < distances[axis]) axis = 2;

    Vector3f normal;
    if (axis == 0) normal = Vector3f(local.GetX() >= 0.0f ? 1.0f : -1.0f, 0.0f, 0.0f);
    if (axis == 1) normal = Vector3f(0.0f, local.GetY() >= 0.0f ? 1.0f : -1.0f, 0.0f);
    if (axis == 2) normal = Vector3f(0.0f, 0.0f, local.GetZ() >= 0.0f ? 1.0f : -1.0f);

    return IntersectData(true, -(sphere.GetRadius() + distances[axis]), normal);
}

IntersectData IntersectAABBPlane(const AABB& box, const plane& surface)
{
    const Vector3f normal = surface.GetNormal().Normalized();
    const Vector3f center = box.GetCenter();
    const Vector3f halfSize = (box.GetMaxCorner() - box.GetMinCorner()) * 0.5f;
    const float centerDistance = normal.Dot(center) + surface.GetDistance();
    const float projectedRadius = std::fabs(normal.GetX()) * halfSize.GetX()
        + std::fabs(normal.GetY()) * halfSize.GetY()
        + std::fabs(normal.GetZ()) * halfSize.GetZ();
    const float distance = std::fabs(centerDistance) - projectedRadius;
    const Vector3f contactNormal = centerDistance >= 0.0f ? normal * -1.0f : normal;
    return IntersectData(distance <= 0.0f, distance, contactNormal);
}
}

IntersectData Collider::Intersect(const Collider& other) const
{
    if (GetType() == SPHERE && other.GetType() == SPHERE)
    {
        return static_cast<const BoundingSphere*>(this)->IntersectBoundingSphere(
            *static_cast<const BoundingSphere*>(&other));
    }
    if (GetType() == AABB_SHAPE && other.GetType() == AABB_SHAPE)
        return dynamic_cast<const class AABB*>(this)->IntersectAABB(*dynamic_cast<const class AABB*>(&other));
    if (GetType() == PLANE && other.GetType() == SPHERE)
        return static_cast<const plane*>(this)->IntersectBoundingSphere(*static_cast<const BoundingSphere*>(&other));
    if (GetType() == SPHERE && other.GetType() == PLANE)
    {
        IntersectData result = static_cast<const plane*>(&other)->IntersectBoundingSphere(
            *static_cast<const BoundingSphere*>(this));
        return IntersectData(result.getDoesIntersect(), result.getDistance(), result.GetNormal() * -1.0f);
    }
    if (GetType() == SPHERE && other.GetType() == AABB_SHAPE)
        return IntersectSphereAABB(*dynamic_cast<const BoundingSphere*>(this), *dynamic_cast<const class AABB*>(&other));
    if (GetType() == AABB_SHAPE && other.GetType() == SPHERE)
    {
        IntersectData result = IntersectSphereAABB(*dynamic_cast<const BoundingSphere*>(&other), *dynamic_cast<const class AABB*>(this));
        return IntersectData(result.getDoesIntersect(), result.getDistance(), result.GetNormal() * -1.0f);
    }
    if (GetType() == AABB_SHAPE && other.GetType() == PLANE)
        return IntersectAABBPlane(*dynamic_cast<const class AABB*>(this), *dynamic_cast<const plane*>(&other));
    if (GetType() == PLANE && other.GetType() == AABB_SHAPE)
    {
        IntersectData result = IntersectAABBPlane(*dynamic_cast<const class AABB*>(&other), *dynamic_cast<const plane*>(this));
        return IntersectData(result.getDoesIntersect(), result.getDistance(), result.GetNormal() * -1.0f);
    }

    return IntersectData(false, 0.0f, Vector3f());
}