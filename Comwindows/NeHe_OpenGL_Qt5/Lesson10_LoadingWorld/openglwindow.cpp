#include "openglwindow.h"

OpenGLWindow::OpenGLWindow(QWindow *parent) :
    QWindow(parent),
    m_update_pending(false),
    m_animating(false),
    m_context(NULL),
    m_show_full_screen(false)
{
    setSurfaceType(QWindow::OpenGLSurface);
    resize(640, 480);
}

OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::render()
{

}

void OpenGLWindow::initialize()
{
}

void OpenGLWindow::resizeGL(int w, int h)
{
    if(h == 0)
    {
        h = 1;
    }
    if (m_context)
    {
        glViewport(0, 0, w, h);
    }
    m_projection.setToIdentity();
    m_projection.perspective(45.0, (float)w/(float)h, 0.1, 1000);
    m_modelView.setToIdentity();
}

void OpenGLWindow::setAnimating(bool animating)
{
    m_animating = animating;
    if(animating)
    {
        renderLater();
    }
}

void OpenGLWindow::renderLater()
{
    if (!m_update_pending)
    {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void OpenGLWindow::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context)
    {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();
        needsInitialize = true;
    }

    m_context->makeCurrent(this);
    if (needsInitialize)
    {
        initializeOpenGLFunctions();
        initialize();
        const qreal retinaScale = devicePixelRatio();
        resizeGL(width()*retinaScale, height()*retinaScale);
    }
    render();

    m_context->swapBuffers(this);

    if (m_animating)
        renderLater();
}

bool OpenGLWindow::event(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::UpdateRequest:
            m_update_pending = false;
            renderNow();
            return true;
        default:
            return QWindow::event(event);
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent *event)
{
    if (isExposed())
    {
        renderNow();
    }
    QWindow::exposeEvent(event);
}

void OpenGLWindow::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();
    const qreal retinaScale = devicePixelRatio();
    resizeGL(w*retinaScale, h*retinaScale);
    renderNow();
    QWindow::resizeEvent(event);
}

void OpenGLWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_F1:
        {
            m_show_full_screen = !m_show_full_screen;
            if(m_show_full_screen)
            {
                showFullScreen();
            }
            else
            {
                showNormal();
            }
            break;
        }
        case Qt::Key_Escape:
        {
            qApp->exit();
            break;
        }
    }
    QWindow::keyPressEvent(event);
}
