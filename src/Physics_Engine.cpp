#include "Physics_Engine.h"
#include <iostream>
#include "bounding_Sph.h"

void PhysicsEngine::AddPhysicsObject(const PhysicsObject& object)
{
    m_physicsObjects.push_back(object);
}

void PhysicsEngine::handleCollisions()
{
    for(unsigned int i = 0; i < m_physicsObjects.size(); i++)
    {
        for(unsigned int j = i + 1; j < m_physicsObjects.size(); j++)
        {
            IntersectData data = m_physicsObjects[i].GetBoundingSphere().IntersectBoundingSphere(m_physicsObjects[j].GetBoundingSphere());
            if(data.getDoesIntersect())
            {
                m_physicsObjects[i].setVelocity(m_physicsObjects[i].GetVelocity()*-1.0f);
                m_physicsObjects[j].setVelocity(m_physicsObjects[j].GetVelocity()*-1.0f);
            }
        }
    }
}

void PhysicsEngine::Simulate(float deltaTime)
{
    
    for(unsigned int i = 0; i < m_physicsObjects.size(); i++)
    {
        m_physicsObjects[i].Integrate(deltaTime);
    }
    
}
