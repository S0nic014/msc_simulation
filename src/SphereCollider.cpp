#include <ngl/VAOPrimitives.h>
#include "SphereCollider.h"

SphereCollider::SphereCollider(const ngl::Vec3 position, const float radius, const std::string name, const ngl::Vec4 color)
{
    m_radius = radius;
    m_transform.setPosition(position);
    m_name = name;
    m_color = color;
}

void SphereCollider::draw()
{
    ngl::VAOPrimitives::draw(m_name);
}
