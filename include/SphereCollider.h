#pragma once
#include <ngl/Transformation.h>

class SphereCollider
{
private:
    float m_radius = 2.0f;
    ngl::Vec4 m_color = {0.5f, 0.5f, 0.0f, 1.0f};
    std::string m_name;

public:
    SphereCollider(const ngl::Vec3 position, const float radius, const std::string name, const ngl::Vec4 color);
    ngl::Transformation m_transform;

public:
    float radius() const { return m_radius; }
    void setRadius(float value) { m_radius = value; }
    ngl::Vec4 color() const { return m_color; }
    void setColor(ngl::Vec4 newColor) { m_color = newColor; }
    std::string name() const { return m_name; }
    void setName(const std::string &newName) { m_name = newName; }
    void draw();
};