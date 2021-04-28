#include <ngl/Vec4.h>
#include <ngl/VAOPrimitives.h>
#include <fmt/format.h>
#include "Scene.h"

Scene::Scene()
{
    ngl::Vec3 clothPosition = {-10.0f, 10.0f, 0.0f};
    m_cloth = std::make_shared<Cloth>(14, 10, 25, 35, clothPosition);
    addSphereCollider({-5.0f, 4.0f, -2.0f}, 2.0f, {0.8f, 0.2f, 0.0f}, "sphere");
    addSphereCollider({0.0f, 3.0f, 4.0f}, 3.0f, {0.0f, 0.8f, 0.1f}, "sphere");
}

void Scene::timeStep()
{
    m_cloth->windForce(ngl::Vec3(0.5f, 0.0f, 0.2f) * 0.05f);
    m_cloth->applyGravity();
    m_cloth->timeStep();
    for (auto collider : m_sphereColliders)
    {
        m_cloth->sphereCollision(collider->m_transform.getPosition(), collider->radius());
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
            fmt::print("Name {} already exists\n", indexedName);
            id++;
            indexedName = fmt::format("{0}{1}", name, id);
            fmt::print("Generated name: {}\n", indexedName);
        }
    }

    auto newSphere = std::make_shared<SphereCollider>(position, radius, indexedName, color);
    m_sphereColliders.push_back(newSphere);
    fmt::print("Created sphere collider: {}\n", newSphere->name());

    return newSphere;
}

void Scene::registerVAOS()
{
    ngl::VAOPrimitives::createLineGrid("floor", 40, 40, 100);
    ngl::VAOPrimitives::createSphere("particleSphere", 0.1, 100.0f);
    for (auto collider : m_sphereColliders)
    {
        ngl::VAOPrimitives::createSphere(collider->name(), collider->radius(), 100.0f);
    }
}