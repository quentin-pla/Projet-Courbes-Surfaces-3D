#include "polygon.h"

Polygon::Polygon(const QVector<Point *> &points, const QColor &color) {
    m_points = points;
    m_color = color;
}

void Polygon::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) {
    GLObject::draw(program, glFuncs);
}

void Polygon::render() {
    GLObject::render();
}
