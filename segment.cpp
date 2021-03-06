#include "segment.h"

Segment::Segment(Point *a, Point *b, const QColor &color, const bool &drawExtremities) : Discretisation({a, b}) {
    m_drawExtremities = drawExtremities;
    m_points.append({a, b});
    m_color = color;
}

Segment::~Segment() {
    GLObject::~GLObject();
}

void Segment::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                   const QVector<unsigned char> &drawTypes_override) {
    glLineWidth(3);
    GLObject::draw(program, glFuncs);
    if (m_drawExtremities)
        for (Point *point : m_points)
            point->draw(program, glFuncs);
}

void Segment::showExtremities(bool value) {
    m_drawExtremities = value;
}

Point *Segment::getValue(float pos, const QColor &color) const {
    float x = (1 - pos) * getStart()->getX() + pos * getEnd()->getX();
    float y = (1 - pos) * getStart()->getY() + pos * getEnd()->getY();
    float z = (1 - pos) * getStart()->getZ() + pos * getEnd()->getZ();
    return new Point(x, y, z, color);
}

void Segment::render() {
    for (Point *point : m_points) {
        point->setColor(m_color);
        m_vertices.append(point->getCoords());
        m_colors.append(m_color);
        m_normals.append(point->getCoords());
    }
    addVBO(GL_LINES);

    GLObject::render();
}

// GETTERS & SETTERS //

Point *Segment::getStart() const { return m_points.first(); }

Point *Segment::getEnd() const { return m_points.last(); }

void Segment::setStart(Point *p) { m_points[0] = p; }

void Segment::setEnd(Point *p) { m_points[1] = p; }
