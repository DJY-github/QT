#ifndef TEXTUREMAPPINGWINDOW_H
#define TEXTUREMAPPINGWINDOW_H

#include "openglwindow.h"
#include <QOpenGLShaderProgram>

class TextureMappingWindow : public OpenGLWindow
{
    Q_OBJECT
public:
    explicit TextureMappingWindow(QWindow *parent = 0);
    ~TextureMappingWindow();
protected:
    void initialize();
    void render();
    void keyPressEvent(QKeyEvent *event);
private:
    void loadGLTexture();

    void loadShader();
private:
    void initGeometry();
private:
    QOpenGLShaderProgram *m_program;
    GLuint m_posAttr;
    GLuint m_texCoordAttr;
    GLuint m_normalAttr;
    GLuint m_vboIds[2];
    GLuint m_texture[3];

    GLfloat m_xrot;
    GLfloat m_yrot;
    GLfloat m_xspeed;
    GLfloat m_yspeed;
    GLfloat m_z;
    bool m_light;
    bool m_blend;
    GLuint m_filter;
};

#endif // TEXTUREMAPPINGWINDOW_H
