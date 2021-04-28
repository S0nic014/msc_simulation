#pragma once
#include <ngl/Vec3.h>
#include <QtWidgets/QDoubleSpinBox>
#include <QLabel>

class Vec3Widget : public QWidget
{

private:
    void createWidgets();
    void createLayouts();
    void createConnections();

public:
    QLabel *m_label;
    QDoubleSpinBox *m_xField;
    QDoubleSpinBox *m_yField;
    QDoubleSpinBox *m_zField;

public:
    Vec3Widget(QString labelText = QString("Vec3"), ngl::Vec3 defaultValue = {0.0f, 0.0f, 0.0f});
    ngl::Vec3 value() const { return ngl::Vec3(m_xField->value(), m_yField->value(), m_zField->value()); }
    void setValue(ngl::Vec3 newValue);
};