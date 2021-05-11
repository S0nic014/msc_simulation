#pragma once
#include <QtWidgets/QWidget>
#include "Scene.h"
#include "ClothParamsWidget.h"
#include "CollidersWidget.h"

class AttribEditorWidget : public QWidget
{

private:
    ClothParamsWidget *m_clothWidget;
    CollidersWidget *m_collidersWidget;

    Scene *m_scene;

private:
    void createWidgets();
    void createLayouts();
    void createConnections();

public:
    AttribEditorWidget(Scene *scene);
};