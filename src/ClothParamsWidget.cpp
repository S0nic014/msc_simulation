#include "ClothParamsWidget.h"
#include "Util.h"
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
    // Simulation fields
    m_dampingField = new QDoubleSpinBox();
    m_simulationStepField = new QDoubleSpinBox();
    m_constraintIterationsField = new QSpinBox();
    m_gravityField = new QDoubleSpinBox();
    m_windDirectionWidget = new Vec3Widget("Wind:");
    m_dampingField->setSingleStep(0.01);
    m_simulationStepField->setSingleStep(0.1);
    m_gravityField->setSingleStep(0.01);
    m_windDirectionWidget->m_xField->setSingleStep(0.1);
    m_windDirectionWidget->m_yField->setSingleStep(0.1);
    m_windDirectionWidget->m_zField->setSingleStep(0.1);
    // Cloth generation feilds
    m_clothWidthField = new QDoubleSpinBox();
    m_clothHeightField = new QDoubleSpinBox();
    m_particlesWidthField = new QSpinBox();
    m_particlesHeightField = new QSpinBox();
    m_particlesWidthField->setMinimum(3);
    m_particlesHeightField->setMinimum(3);
    m_clothPositionWidget = new Vec3Widget("Position:");
    m_generateClothButton = new QPushButton("Generate");
}
void ClothParamsWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow("Damping:", m_dampingField);
    mainLayout->addRow("Step:", m_simulationStepField);
    mainLayout->addRow("Constraint iterations:", m_constraintIterationsField);
    mainLayout->addRow("Gravity:", m_gravityField);
    mainLayout->addRow(m_windDirectionWidget);
    mainLayout->addRow(addSeparator());
    mainLayout->addRow("Width:", m_clothWidthField);
    mainLayout->addRow("Height:", m_clothHeightField);
    mainLayout->addRow("Particles width:", m_particlesWidthField);
    mainLayout->addRow("Particles height:", m_particlesHeightField);
    mainLayout->addRow(m_clothPositionWidget);
    mainLayout->addRow(m_generateClothButton);
    setLayout(mainLayout);
}
void ClothParamsWidget::createConnections()
{
    // Cloth connections
    connect(this->m_dampingField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    connect(this->m_simulationStepField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    connect(this->m_constraintIterationsField, SIGNAL(valueChanged(int)), this, SLOT(updateCloth()));
    connect(this->m_gravityField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    connect(this->m_windDirectionWidget->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    connect(this->m_windDirectionWidget->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    connect(this->m_windDirectionWidget->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateCloth()));
    // Scene connections
    connect(this->m_generateClothButton, SIGNAL(clicked()), this, SLOT(generateCloth()));
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
        m_clothWidthField->setValue(m_scene->clothObject()->width());
        m_clothHeightField->setValue(m_scene->clothObject()->height());
        m_particlesWidthField->setValue(m_scene->clothObject()->numParticlesWidth());
        m_particlesHeightField->setValue(m_scene->clothObject()->numParticlesHeight());
        m_clothPositionWidget->setValue(m_scene->clothObject()->transform().getPosition());
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

void ClothParamsWidget::generateCloth()
{
    //Collect values
    float width = m_clothWidthField->value();
    float height = m_clothHeightField->value();
    int particlesWidth = m_particlesWidthField->value();
    int particlesHeight = m_particlesHeightField->value();
    ngl::Vec3 position = m_clothPositionWidget->value();

    m_scene->generateCloth(width, height, particlesWidth, particlesHeight, position);
}
