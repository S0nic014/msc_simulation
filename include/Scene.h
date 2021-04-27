#ifndef SCENE_H_
#define SCENE_H_
#include <vector>
#include <memory>
#include <ngl/Vec3.h>
#include <QtCore/QObject>

class Scene : public QObject
{
    Q_OBJECT
public:
    Scene();

signals:
    void changed();
};

#endif