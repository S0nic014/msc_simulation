#pragma once
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QPushButton>
#include "Cloth.h"
#include "Scene.h"
#include "Vec3Widget.h"

class ClothParamsWidget : public QGroupBox
{
    Q_OBJECT

private:
    Scene *m_scene;
    // Simulation fields
    QDoubleSpinBox *m_dampingField;
    QDoubleSpinBox *m_simulationStepField;
    QSpinBox *m_constraintIterationsField;
    QDoubleSpinBox *m_gravityField;
    Vec3Widget *m_windDirectionWidget;
    // Cloth generation fields
    QDoubleSpinBox *m_clothWidthField;
    QDoubleSpinBox *m_clothHeightField;
    QSpinBox *m_particlesWidthField;
    QSpinBox *m_particlesHeightField;
    Vec3Widget *m_clothPositionWidget;
    QPushButton *m_generateClothButton;

private:
    void createWidgets();
    void createLayouts();
    void createConnections();

public:
    ClothParamsWidget(Scene *scene);

public slots:
    void generateCloth();
    void updateValues();
    void updateCloth();
};