#pragma once
#include <QtWidgets/QWidget>
#include "Scene.h"
#include "ClothParamsWidget.h"

class AttribEditorWidget : public QWidget
{

private:
    ClothParamsWidget *m_clothWidget;
    Scene *m_scene;

private:
    void createWidgets();
    void createLayouts();
    void createConnections();

public:
    AttribEditorWidget(Scene *scene);
};