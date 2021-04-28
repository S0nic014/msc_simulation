#include "AttribEditorWidget.h"
#include <QtWidgets/QVBoxLayout>

AttribEditorWidget ::AttribEditorWidget(Scene *scene)
{
    m_scene = scene;
    createWidgets();
    createLayouts();
    createConnections();
}

void AttribEditorWidget::createWidgets()
{
    m_clothWidget = new ClothParamsWidget(m_scene);
}

void AttribEditorWidget::createLayouts()
{

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_clothWidget);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void AttribEditorWidget::createConnections()
{
}