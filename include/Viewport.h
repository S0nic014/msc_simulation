#pragma once
#include "WindowParams.h"
#include <ngl/Transformation.h>
#include "Scene.h"
// this must be included after NGL includes else we get a clash with gl libs
#include <QtWidgets/QOpenGLWidget>

class Viewport : public QOpenGLWidget
{
public:
    Viewport();
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int _w, int _h) override;
    Scene *scene() const { return m_scene; }
    void timerEvent(QTimerEvent *) override;

private:
    //Qt Events
    void keyPressEvent(QKeyEvent *_event) override;
    void mouseMoveEvent(QMouseEvent *_event) override;
    void mousePressEvent(QMouseEvent *_event) override;
    void mouseReleaseEvent(QMouseEvent *_event) override;
    void wheelEvent(QWheelEvent *_event) override;
    // GL
    void loadMatrixToColourShader(ngl::Transformation &_tx);

private:
    WinParams m_win;
    ngl::Vec3 m_modelPos;
    ngl::Mat4 m_view;
    ngl::Mat4 m_project;
    ngl::Mat4 m_globalMouseTX;
    Scene *m_scene;
};
