#include <iostream>
#include <QtWidgets/QMenuBar>
#include <QtGui/QColor>
#include "MainWindow.h"
#include "AttribEditorWidget.h"

MainWindow::MainWindow()
{
    setWindowTitle("ClothNGL");
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    createActions();
    createMenuBar();
    createWidgets();
    createLayouts();
    createConnections();
}

void MainWindow::createActions()
{
    m_showAttribEditorAction = new QAction("Attribute editor");
}

void MainWindow::createMenuBar()
{
    setMenuBar(new QMenuBar());
    // Windows
    QMenu *windowsMenu = new QMenu("Windows");
    windowsMenu->addAction(m_showAttribEditorAction);
    //Add menus
    menuBar()->addMenu(windowsMenu);
}

void MainWindow::createWidgets()
{
    m_mainWidget = new QWidget();
    setCentralWidget(m_mainWidget);
    m_viewport = new Viewport();
    AttribEditorWidget *attribEditor = new AttribEditorWidget(m_viewport->scene());

    //Attrib dock
    m_attribEditorDock = new QDockWidget(tr("Attribute Editor"), this);
    m_attribEditorDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    m_attribEditorDock->setWidget(attribEditor);
    addDockWidget(Qt::RightDockWidgetArea, m_attribEditorDock);
}

void MainWindow::createLayouts()
{
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addWidget(m_viewport);
    m_mainWidget->setLayout(m_mainLayout);
}

void MainWindow::createConnections()
{
    connect(m_showAttribEditorAction, SIGNAL(triggered()), m_attribEditorDock, SLOT(show()));
}

QPalette *MainWindow::darkPalette()
{
    QPalette *darkPalette = new QPalette();
    darkPalette->setColor(QPalette::Window, QColor(45, 45, 45));
    darkPalette->setColor(QPalette::WindowText, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette->setColor(QPalette::AlternateBase, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::ToolTipBase, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::Text, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::Button, QColor(45, 45, 45));
    darkPalette->setColor(QPalette::ButtonText, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::BrightText, Qt::red);
    darkPalette->setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette->setColor(QPalette::Link, Qt::gray);
    return darkPalette;
}