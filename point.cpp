#include "point.h"
#include "iostream"

Point::Point(QColor *color, float size) {
    m_coords = QVector3D(0, 0, 0);
    m_color = *color;
    m_size = size;
    vertices.append(m_coords);
    colors.append(m_color);
    addVBO(GL_POINTS);
}

Point::Point(float x, float y, float z, QColor *color, float size) : Point(color, size) {
    m_coords = QVector3D(x, y, z);
}

Point::Point(const Point &p) : Point(p.getX(), p.getY(), p.getZ(), new QColor(p.getColor()), p.getSize()) {}

void Point::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                 QMatrix4x4& world_mat, QMatrix4x4& proj_mat, QMatrix4x4& cam_mat, QMatrix4x4& shape_mat) {
    glPointSize(m_size);
    GLObject::draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
}

void Point::applyTransforms(QMatrix4x4 &mat) {
    mat.translate(getCoords());
}

// GETTERS & SETTERS //

QVector3D Point::getCoords() const { return m_coords; }

QColor Point::getColor() const { return m_color; }

float Point::getSize() const { return m_size; }

float Point::getX() const { return m_coords.x(); }

float Point::getY() const { return m_coords.y(); }

float Point::getZ() const { return m_coords.z(); }

void Point::setCoords(const QVector3D &newCoords) { m_coords = newCoords; }

void Point::setX(const float &v) { m_coords.setX(v); }

void Point::setY(const float &v) { m_coords.setY(v); }

void Point::setZ(const float &v) { m_coords.setZ(v); }