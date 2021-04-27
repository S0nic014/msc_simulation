#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDockWidget>
#include <QtGui/QPalette>
#include "Viewport.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow();
    static QPalette *darkPalette();

private:
    void createActions();
    void createMenuBar();
    void createWidgets();
    void createLayouts();
    void createConnections();

private:
    // Actions
    QAction *m_showAttribEditorAction;
    // Widgets
    QDockWidget *m_attribEditorDock;
    Viewport *m_viewport;
    QVBoxLayout *m_mainLayout;
    QWidget *m_mainWidget;
};

#endif