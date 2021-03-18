#include "polygon.h"

Polygon::Polygon(const QVector<Point *> &points, const QColor &color, bool drawExtremities) {
    m_points = points;
    m_color = color;
    m_drawExtremities = drawExtremities;

    for (Point *point : m_points)
        point->setColor(color);
}

void Polygon::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                   const QVector<unsigned char> &drawTypes_override) {
    glLineWidth(3);
    GLObject::draw(program, glFuncs);
    if (m_drawExtremities)
        for (Point *point : m_points)
            point->draw(program, glFuncs);
}

void Polygon::render() {
    QVector3D normal = generateNormal(m_points[0]->getCoords(), m_points[1]->getCoords(),
                                      m_points[2]->getCoords());
    for (Point *point : m_points) {
        m_vertices.append(point->getCoords());
        m_colors.append(point->getColor());
        m_normals.append(normal);
    }
    addVBO(GL_POLYGON);
    GLObject::render();
}

void Polygon::showExtremities(bool value) {
    m_drawExtremities = value;
}

const QVector<Point *> &Polygon::getPoints() const {
    return m_points;
}
