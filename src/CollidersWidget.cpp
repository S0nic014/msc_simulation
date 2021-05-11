#include <ngl/VAOPrimitives.h>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QHBoxLayout>
#include "CollidersWidget.h"

CollidersWidget::CollidersWidget(Scene *scene)
{
    setTitle("Colliders");
    m_scene = scene;
    createWidgets();
    createLayouts();
    updateList();
    createConnections();
    m_moveStepSizeField->setValue(0.1);
}

void CollidersWidget::createWidgets()
{
    m_collidersList = new QListWidget();
    m_moveStepSizeField = new QDoubleSpinBox();
    m_moveStepSizeField->setSingleStep(0.1);
    m_positionWidget = new Vec3Widget("Position:");
}
void CollidersWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow(m_collidersList);
    mainLayout->addRow("Move step:", m_moveStepSizeField);
    mainLayout->addRow(m_positionWidget);
    setLayout(mainLayout);
}
void CollidersWidget::createConnections()
{
    connect(this->m_collidersList, SIGNAL(currentRowChanged(int)), this, SLOT(updateSelectedColliderData()));
    connect(this->m_positionWidget->m_xField, SIGNAL(valueChanged(double)), this, SLOT(setSelectionPosition()));
    connect(this->m_positionWidget->m_yField, SIGNAL(valueChanged(double)), this, SLOT(setSelectionPosition()));
    connect(this->m_positionWidget->m_zField, SIGNAL(valueChanged(double)), this, SLOT(setSelectionPosition()));
    connect(this->m_moveStepSizeField, SIGNAL(valueChanged(double)), this, SLOT(setMoveStepSize(double)));
}

void CollidersWidget::updateList()
{
    m_collidersList->clear();
    for (auto col : m_scene->allSphereColliders())
    {
        QListWidgetItem *colliderItem = new QListWidgetItem(col->qname());
        m_collidersList->addItem(colliderItem);
    }
}

void CollidersWidget::updateSelectedColliderData()
{
    if (!m_collidersList->currentItem())
    {
        return;
    }
    unsigned int currentRow = m_collidersList->currentIndex().row();
    m_positionWidget->setValue(m_scene->sphereColliderAt(currentRow)->position());
}

void CollidersWidget::setSelectionPosition()
{
    if (!m_collidersList->currentItem())
    {
        return;
    }
    unsigned int currentRow = m_collidersList->currentIndex().row();
    m_scene->sphereColliderAt(currentRow)->setPosition(m_positionWidget->value());
}

void CollidersWidget::setMoveStepSize(const double stepSize)
{
    m_positionWidget->m_xField->setSingleStep(stepSize);
    m_positionWidget->m_yField->setSingleStep(stepSize);
    m_positionWidget->m_zField->setSingleStep(stepSize);
}