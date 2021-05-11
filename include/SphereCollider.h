#pragma once
#include <ngl/Transformation.h>
#include <QtCore/QString>

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
    QString qname() const { return QString::fromUtf8(m_name.c_str()); }
    void setName(const std::string &newName) { m_name = newName; }
    ngl::Vec3 position() const { return m_transform.getPosition(); }
    void setPosition(const ngl::Vec3 newPosition) { m_transform.setPosition(newPosition); }
    void offsetPosition(const ngl::Vec3 offset) { m_transform.addPosition(offset); }
    void draw();
};