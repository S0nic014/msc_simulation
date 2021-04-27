#include <fmt/format.h>
#include "ngl/Vec4.h"
#include "Scene.h"

Scene::Scene()
{
    m_cloth = std::make_shared<Cloth>(14, 10, 45, 55);
}