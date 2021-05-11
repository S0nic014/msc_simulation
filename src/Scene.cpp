#include <ngl/Vec4.h>
#include <ngl/VAOPrimitives.h>
#include <fmt/format.h>
#include "Scene.h"

Scene::Scene()
{
    ngl::Vec3 clothPosition = {-10.0f, 10.0f, 0.0f};
    generateCloth(14, 10, 35, 50, clothPosition);
    setWindDirection(ngl::Vec3(0.2f, 0.0f, 0.2f));
    addSphereCollider({-5.0f, 6.0f, 3.0f}, 2.0f, {0.8f, 0.2f, 0.0f}, "sphere");
    addSphereCollider({0.0f, 3.0f, 4.0f}, 3.0f, {0.0f, 0.8f, 0.1f}, "sphere");
}

void Scene::timeStep()
{
    if (m_cloth)
    {
        m_cloth->windForce(m_windDirection * m_cloth->stepSize2());
        m_cloth->applyGravity();
        m_cloth->timeStep();
        for (auto collider : m_sphereColliders)
        {
            m_cloth->sphereCollision(collider->m_transform.getPosition(), collider->radius());
        }
    }
}

std::shared_ptr<SphereCollider> Scene::sphereColliderAt(unsigned int index)
{
    if (index > m_sphereColliders.size())
    {
        return nullptr;
    }
    return m_sphereColliders.at(index);
}

std::shared_ptr<SphereCollider> Scene::addSphereCollider(const ngl::Vec3 position, const float radius, const ngl::Vec4 color, const std::string name)
{
    // Generate unique name
    unsigned int id = 1;
    std::string indexedName = fmt::format("{0}{1}", name, id);
    for (auto existingCollider : m_sphereColliders)
    {
        if (indexedName == existingCollider->name())
        {
            id++;
            indexedName = fmt::format("{0}{1}", name, id);
        }
    }

    auto newSphere = std::make_shared<SphereCollider>(position, radius, indexedName, color);
    m_sphereColliders.push_back(newSphere);
    emit changed();
    fmt::print("Created sphere collider: {}\n", newSphere->name());

    return newSphere;
}

void Scene::generateCloth(const float width, const float height, const unsigned int numParticlesWidth, const unsigned int numParticlesHeight, ngl::Vec3 atPosition)
{
    m_cloth = std::make_shared<Cloth>(width, height, numParticlesWidth, numParticlesHeight, atPosition);
    emit changed();
}

void Scene::registerVAOS()
{
    ngl::VAOPrimitives::createLineGrid("floor", 40, 40, 100);
    ngl::VAOPrimitives::createSphere("particleSphere", 0.1f, 100.0f);
    for (auto collider : m_sphereColliders)
    {
        ngl::VAOPrimitives::createSphere(collider->name(), collider->radius(), 100.0f);
    }
}