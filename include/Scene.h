#pragma once
#include <vector>
#include <memory>
#include <ngl/Vec3.h>
#include <QtCore/QObject>
#include "Cloth.h"
#include "SphereCollider.h"

class Scene : public QObject
{
    Q_OBJECT
private:
    std::shared_ptr<Cloth> m_cloth;
    std::vector<std::shared_ptr<SphereCollider>> m_sphereColliders;

public:
    Scene();
    std::shared_ptr<Cloth> clothObject() const { return m_cloth; };
    std::vector<std::shared_ptr<SphereCollider>> allSphereColliders() const { return m_sphereColliders; };
    std::shared_ptr<SphereCollider> sphereColliderAt(unsigned int index);
    std::shared_ptr<SphereCollider> addSphereCollider(const ngl::Vec3 position = {0.0f, 0.0f, 0.0f}, const float radius = 1.0f, const ngl::Vec4 color = {0.8f, 0.2f, 0.0f}, const std::string name = "sphere");
    void registerVAOS();
    void timeStep();

signals:
    void changed();
};
