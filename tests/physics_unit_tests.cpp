#include "aabb.h"
#include "bounding_Sph.h"
#include "collider.h"
#include "plane.h"
#include "physics_object.h"

#include <cmath>
#include <iostream>
#include <string>

namespace
{
const float EPSILON = 1e-5f;
int failures = 0;

void Expect(bool condition, const std::string& description)
{
    if (!condition)
    {
        std::cerr << "FAIL: " << description << std::endl;
        ++failures;
    }
}

void ExpectNear(float actual, float expected, const std::string& description)
{
    Expect(std::fabs(actual - expected) <= EPSILON, description);
}

void TestVectorMath()
{
    const Vector3f xAxis(1.0f, 0.0f, 0.0f);
    const Vector3f yAxis(0.0f, 1.0f, 0.0f);
    const Vector3f cross = xAxis.Cross(yAxis);

    Expect(cross == Vector3f(0.0f, 0.0f, 1.0f), "cross product follows the right-hand rule");
    ExpectNear(Vector3f(3.0f, 4.0f, 0.0f).Normalized().Length(), 1.0f, "normalized vector has unit length");
}

void TestBoundingSpheres()
{
    const BoundingSphere origin(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
    const BoundingSphere overlapping(Vector3f(1.5f, 0.0f, 0.0f), 1.0f);
    const BoundingSphere touching(Vector3f(2.0f, 0.0f, 0.0f), 1.0f);
    const BoundingSphere separated(Vector3f(3.0f, 0.0f, 0.0f), 1.0f);

    Expect(origin.IntersectBoundingSphere(overlapping).getDoesIntersect(), "overlapping spheres intersect");
    Expect(origin.IntersectBoundingSphere(touching).getDoesIntersect(), "touching spheres intersect");
    Expect(!origin.IntersectBoundingSphere(separated).getDoesIntersect(), "separated spheres do not intersect");
    ExpectNear(origin.IntersectBoundingSphere(overlapping).getDistance(), -0.5f, "sphere distance is surface separation");
}

void TestAabbs()
{
    const AABB first(Vector3f(-1.0f, -1.0f, -1.0f), Vector3f(1.0f, 1.0f, 1.0f));
    const AABB overlapping(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(2.0f, 2.0f, 2.0f));
    const AABB separated(Vector3f(2.0f, 0.0f, 0.0f), Vector3f(3.0f, 1.0f, 1.0f));

    Expect(first.IntersectAABB(overlapping).getDoesIntersect(), "overlapping AABBs intersect");
    Expect(!first.IntersectAABB(separated).getDoesIntersect(), "separated AABBs do not intersect");
}

void TestColliderDispatch()
{
    const BoundingSphere sphere(Vector3f(0.0f, 0.5f, 0.0f), 1.0f);
    const AABB box(Vector3f(-1.0f, -1.0f, -1.0f), Vector3f(1.0f, 1.0f, 1.0f));
    const plane ground(Vector3f(0.0f, 1.0f, 0.0f), 0.0f);

    Expect(sphere.Intersect(box).getDoesIntersect(), "sphere-to-AABB dispatch detects contact");
    Expect(box.Intersect(sphere).getDoesIntersect(), "AABB-to-sphere dispatch detects contact");
    Expect(ground.Intersect(sphere).getDoesIntersect(), "plane-to-sphere dispatch detects contact");
    Expect(sphere.Intersect(ground).getDoesIntersect(), "sphere-to-plane dispatch detects contact");
    Expect(box.Intersect(ground).getDoesIntersect(), "AABB-to-plane dispatch detects contact");
    Expect(ground.Intersect(box).getDoesIntersect(), "plane-to-AABB dispatch detects contact");
}

void TestPhysicsObjectMotion()
{
    PhysicsObject moving(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 0.0f, 0.0f), 1.0f);
    moving.Integrate(0.5f);
    const BoundingSphere& sphere = dynamic_cast<const BoundingSphere&>(moving.GetCollider());
    ExpectNear(sphere.GetCenter().GetX(), 1.0f, "dynamic body moves its collider with velocity");

    PhysicsObject staticBody(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 0.0f, 0.0f), 1.0f, 0.0f);
    staticBody.Integrate(0.5f);
    const BoundingSphere& staticSphere = dynamic_cast<const BoundingSphere&>(staticBody.GetCollider());
    ExpectNear(staticSphere.GetCenter().GetX(), 0.0f, "zero-mass body remains static");
}

void TestPlanes()
{
    const plane ground(Vector3f(0.0f, 1.0f, 0.0f), 0.0f);
    const BoundingSphere aboveGround(Vector3f(0.0f, 2.0f, 0.0f), 1.0f);
    const BoundingSphere crossingGround(Vector3f(0.0f, 0.5f, 0.0f), 1.0f);

    Expect(!ground.IntersectBoundingSphere(aboveGround).getDoesIntersect(), "sphere above plane does not intersect");
    Expect(ground.IntersectBoundingSphere(crossingGround).getDoesIntersect(), "sphere crossing plane intersects");
}
}

int main()
{
    TestVectorMath();
    TestBoundingSpheres();
    TestAabbs();
    TestPlanes();
    TestColliderDispatch();
    TestPhysicsObjectMotion();

    if (failures != 0)
    {
        std::cerr << failures << " test(s) failed" << std::endl;
        return 1;
    }

    std::cout << "All physics unit tests passed" << std::endl;
    return 0;
}
