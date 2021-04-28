#include "ClothParamsWidget.h"
#include <QtWidgets/QFormLayout>

ClothParamsWidget ::ClothParamsWidget(Scene *scene)
{
    m_scene = scene;
    setTitle("Cloth");
    createWidgets();
    createLayouts();
    updateValues();
    createConnections();
}

void ClothParamsWidget::createWidgets()
{
    m_dampingField = new QDoubleSpinBox();
    m_simulationStepField = new QDoubleSpinBox();
    m_constraintIterationsField = new QSpinBox();
    m_gravityField = new QDoubleSpinBox();
    m_windDirectionWidget = new Vec3Widget("Wind:");
    m_dampingField->setSingleStep(0.1);
    m_simulationStepField->setSingleStep(0.1);
    m_gravityField->setSingleStep(0.1);
    m_windDirectionWidget->m_xField->setSingleStep(0.1);
    m_windDirectionWidget->m_yField->setSingleStep(0.1);
    m_windDirectionWidget->m_zField->setSingleStep(0.1);
}
void ClothParamsWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow("Damping:", m_dampingField);
    mainLayout->addRow("Step:", m_simulationStepField);
    mainLayout->addRow("Constraint iterations:", m_constraintIterationsField);
    mainLayout->addRow("Gravity:", m_gravityField);
    mainLayout->addRow(m_windDirectionWidget);
    setLayout(mainLayout);
}
void ClothParamsWidget::createConnections()
{
    connect(this->m_dampingField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    connect(this->m_simulationStepField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    connect(this->m_constraintIterationsField, SIGNAL(valueChanged(int)), this, SLOT(updateCloth()));
    connect(this->m_gravityField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    connect(this->m_windDirectionWidget->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    connect(this->m_windDirectionWidget->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    connect(this->m_windDirectionWidget->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
}

void ClothParamsWidget::updateValues()
{
    m_windDirectionWidget->setValue(m_scene->windDirection());
    if (m_scene->clothObject())
    {
        m_dampingField->setValue(m_scene->clothObject()->damping());
        m_simulationStepField->setValue(m_scene->clothObject()->stepSize());
        m_constraintIterationsField->setValue(m_scene->clothObject()->constraintIterations());
        m_gravityField->setValue(m_scene->clothObject()->gravity());
    }
}

void ClothParamsWidget::updateCloth()
{
    m_scene->setWindDirection(m_windDirectionWidget->value());
    if (m_scene->clothObject())
    {
        m_scene->clothObject()->setDamping(m_dampingField->value());
        m_scene->clothObject()->setStepSize(m_simulationStepField->value());
        m_scene->clothObject()->setConstraintIterations(m_constraintIterationsField->value());
        m_scene->clothObject()->setGravity(m_gravityField->value());
    }
}