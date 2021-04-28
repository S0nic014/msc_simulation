#pragma once
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDoubleSpinBox>
#include "Cloth.h"
#include "Scene.h"
#include "Vec3Widget.h"

class ClothParamsWidget : public QGroupBox
{
    Q_OBJECT

private:
    Scene *m_scene;
    std::shared_ptr<Cloth> m_cloth;
    QDoubleSpinBox *m_dampingField;
    QDoubleSpinBox *m_simulationStepField;
    QSpinBox *m_constraintIterationsField;
    QDoubleSpinBox *m_gravityField;
    Vec3Widget *m_windDirectionWidget;

private:
    void createWidgets();
    void createLayouts();
    void createConnections();

public:
    ClothParamsWidget(Scene *scene);

public slots:
    void updateValues();
    void updateCloth();
};