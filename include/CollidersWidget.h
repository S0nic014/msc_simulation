#pragma once
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QPushButton>
#include "Vec3Widget.h"
#include "Scene.h"

class CollidersWidget : public QGroupBox
{
    Q_OBJECT
private:
    QListWidget *m_collidersList;
    Vec3Widget *m_positionWidget;
    QDoubleSpinBox *m_moveStepSizeField;
    Scene *m_scene;

private:
    void createWidgets();
    void createLayouts();
    void createConnections();

public:
    CollidersWidget(Scene *scene);

public slots:
    void updateList();
    void updateSelectedColliderData();
    void setSelectionPosition();
    void setMoveStepSize(const double stepSize);
};