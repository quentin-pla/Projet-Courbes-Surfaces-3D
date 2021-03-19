#include "polygon.h"

Polygon::Polygon(const QVector<Point *> &points, const QColor &color, bool drawExtremities) {
    m_points = points;
    m_color = color;
    m_drawExtremities = drawExtremities;
    m_points_normals = false;

    for (Point *point : m_points)
        point->setColor(color);
}

Polygon::~Polygon() {
    GLObject::~GLObject();
}


void Polygon::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                   const QVector<unsigned char> &drawTypes_override) {
    glLineWidth(m_line_width);
    if (drawTypes_override.isEmpty())
        GLObject::draw(program, glFuncs, {GL_POLYGON});
    else
        GLObject::draw(program, glFuncs, drawTypes_override);
    if (m_drawExtremities) {
        glPointSize(15);
        for (Point *point : m_points)
            point->draw(program, glFuncs);
    }
}

void Polygon::render() {
    QVector3D polygon_normal = generateNormal(m_points[0]->getCoords(), m_points[1]->getCoords(),
                                              m_points[2]->getCoords());
    for (Point *point : m_points) {
        m_vertices.append(point->getCoords());
        m_colors.append(point->getColor());
        m_normals.append(m_points_normals ? point->getCoords() : polygon_normal);
    }
    addVBO(GL_POINTS);
    GLObject::render();
}

void Polygon::showExtremities(bool value) {
    m_drawExtremities = value;
}

const QVector<Point *> &Polygon::getPoints() const {
    return m_points;
}

void Polygon::setLineWidth(int lineWidth) {
    m_line_width = lineWidth;
}

void Polygon::enablePointsNormals(bool value) {
    m_points_normals = value;
}