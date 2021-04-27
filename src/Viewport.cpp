#include <iostream>
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/SimpleVAO.h>
#include <ngl/VAOFactory.h>
#include <ngl/Util.h>
#include <QtGui/QSurfaceFormat>
#include "Viewport.h"
#include "Cloth.h"

Viewport::Viewport()
{
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    // Set format
    QSurfaceFormat format;
    format.setSamples(4);
#if defined(__APPLE__)
    // at present mac osx Mountain Lion only supports GL3.2
    // the new mavericks will have GL 4.x so can change
    format.setMajorVersion(4);
    format.setMinorVersion(1);
#else
    // with luck we have the latest GL version so set to this
    format.setMajorVersion(4);
    format.setMinorVersion(3);
#endif
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    setFormat(format);

    // Create scene etc
    m_scene = new Scene();
}
void Viewport::resizeGL(int _w, int _h)
{
    m_win.width = static_cast<int>(_w * devicePixelRatio());
    m_win.height = static_cast<int>(_h * devicePixelRatio());
    m_project = ngl::perspective(45.0f, static_cast<float>(_w) / _h, 0.1f, 80.0f);
}

void Viewport::initializeGL()
{
    // we must call that first before any other GL commands to load and link the
    // gl commands from the lib, if that is not done program will crash
    ngl::NGLInit::initialize();
    glClearColor(0.4f, 0.4f, 0.4f, 0.4f); // Grey Background
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // enable multisampling for smoother drawing
    glEnable(GL_MULTISAMPLE);
    ngl::VAOPrimitives::createLineGrid("floor", 40, 40, 100);
    ngl::VAOPrimitives::createSphere("particleSphere", 0.1, 100);
    m_view = ngl::lookAt({0.0f, 20.0f, 20.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    startTimer(10);
}

void Viewport::loadMatrixToColourShader(ngl::Transformation &_tx)
{
    ngl::ShaderLib::setUniform("MVP", m_project * m_view * m_globalMouseTX * _tx.getMatrix());
}

void Viewport::paintGL()
{
    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_win.width, m_win.height);
    // Mouse rotation
    ngl::Mat4 rotX, rotY;
    rotX.rotateX(m_win.spinXFace);
    rotY.rotateY(m_win.spinYFace);
    m_globalMouseTX = rotX * rotY;
    m_globalMouseTX.m_30 = m_modelPos.m_x;
    m_globalMouseTX.m_31 = m_modelPos.m_y;
    m_globalMouseTX.m_32 = m_modelPos.m_z;
    // Load shaders
    ngl::Transformation tx;
    ngl::ShaderLib::use(ngl::nglColourShader);
    loadMatrixToColourShader(tx);
    ngl::ShaderLib::setUniform("Colour", 0.6f, 0.6f, 0.6f, 1.0f);
    // Draw objects
    ngl::VAOPrimitives::draw("floor");
    if (m_scene->clothObject() != nullptr)
    {
        for (auto particle : m_scene->clothObject()->particles())
        {
            tx.setPosition(particle->position());
            ngl::ShaderLib::setUniform("Colour", 0.0f, 0.0f, 0.8f, 1.0f);
            loadMatrixToColourShader(tx);
            particle->drawSphere();
        }
    }
}

void Viewport::timerEvent(QTimerEvent *)
{
    m_scene->clothObject()->windForce(ngl::Vec3(0.5f, 0.0f, 0.2f) * 0.05f);
    m_scene->clothObject()->timeStep();
    update();
}
