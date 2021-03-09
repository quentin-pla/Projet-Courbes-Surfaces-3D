#include "segment.h"

Segment::Segment(Point* a, Point* b, const bool &drawExtremities) : Discretisation({a,b}) {
    m_drawExtremities = drawExtremities;
    m_points.append({a, b});
    for (Point* point : m_points) {
        vertices.append(point->getCoords());
        colors.append(point->getColor());
    }
    addVBO(GL_LINES);
}

void Segment::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                   QMatrix4x4& world_mat, QMatrix4x4& proj_mat, QMatrix4x4& cam_mat, QMatrix4x4& shape_mat) {
    if (m_drawExtremities)
        for (Point *point : m_points)
            point->draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
    GLObject::draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
}

void Segment::showExtremities(bool value) {
    m_drawExtremities = value;
}

Point *Segment::getValue(float pos, const QColor &color) const {
    float x = (1 - pos) * getStart()->getX() + pos * getEnd()->getX();
    float y = (1 - pos) * getStart()->getY() + pos * getEnd()->getY();
    float z = (1 - pos) * getStart()->getZ() + pos * getEnd()->getZ();
    return new Point(x, y, z, new QColor(color));
}

// GETTERS & SETTERS //

Point* Segment::getStart() const { return m_points.first(); }

Point* Segment::getEnd() const { return m_points.last(); }

void Segment::setStart(Point* p) { m_points[0] = p; }

void Segment::setEnd(Point* p) { m_points[1] = p; }
