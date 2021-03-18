#include "polyedre.h"

Polyedre::Polyedre(const QVector<Point *> &points, const QColor &color) {
    m_points = points;
    m_color = color;
}

void Polyedre::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) {
    GLObject::draw(program, glFuncs);

}

void Polyedre::render() {
    GLObject::render();
}
