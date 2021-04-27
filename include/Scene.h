#ifndef SCENE_H_
#define SCENE_H_
#include <vector>
#include <memory>
#include <ngl/Vec3.h>
#include <QtCore/QObject>
#include "Cloth.h"

class Scene : public QObject
{
    Q_OBJECT
private:
    std::shared_ptr<Cloth> m_cloth;

public:
    Scene();
    std::shared_ptr<Cloth> clothObject() const { return m_cloth; };

signals:
    void changed();
};

#endif