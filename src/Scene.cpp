#include <fmt/format.h>
#include "ngl/Vec4.h"
#include "Scene.h"

Scene::Scene()
{
    ngl::Vec3 clothPosition = {-10.0f, 10.0f, 0.0f};
    m_cloth = std::make_shared<Cloth>(14, 10, 45, 55, clothPosition);
}

void Scene::timeStep()
{
    m_cloth->windForce(ngl::Vec3(0.5f, 0.0f, 0.2f) * 0.05f);
    m_cloth->applyGravity();
    m_cloth->timeStep();
}