#include "Vec3Widget.h"
#include <QtWidgets/QGridLayout>

Vec3Widget::Vec3Widget(QString labelText, ngl::Vec3 defaultValue)
{
    createWidgets();
    createLayouts();
    createConnections();
    m_label->setText(labelText);
    setValue(defaultValue);
}

void Vec3Widget::createWidgets()
{
    m_label = new QLabel;
    m_xField = new QDoubleSpinBox();
    m_yField = new QDoubleSpinBox();
    m_zField = new QDoubleSpinBox();
    m_xField->setRange(-9999.0, 9999.0);
    m_yField->setRange(-9999.0, 9999.0);
    m_zField->setRange(-9999.0, 9999.0);
}
void Vec3Widget::createLayouts()
{
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(m_label, 0, 0);
    mainLayout->addWidget(m_xField, 0, 1);
    mainLayout->addWidget(m_yField, 0, 2);
    mainLayout->addWidget(m_zField, 0, 3);
    setLayout(mainLayout);
}
void Vec3Widget::createConnections()
{
}

void Vec3Widget::setValue(ngl::Vec3 newValue)
{
    m_xField->setValue(newValue.m_x);
    m_yField->setValue(newValue.m_y);
    m_zField->setValue(newValue.m_z);
}