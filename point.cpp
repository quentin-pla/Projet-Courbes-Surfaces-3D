#include "point.h"

Point::Point(QColor *color, float size) {
    m_coords = {0, 0, 0};
    m_color = color;
    m_size = size;
}

Point::Point(float x, float y, float z, QColor *color, float size) : Point(color, size) {
    m_coords = {x, y, z};
}

void Point::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) {
    glPointSize(m_size);
    GLObject::draw(program, glFuncs);
}

void Point::render() {
    vertices.append(m_coords);
    colors.append(*m_color);
    normals.append(m_coords);
    addVBO(GL_POINTS);
    GLObject::render();
}

// GETTERS & SETTERS //

QVector3D Point::getCoords() const { return m_coords; }

QColor Point::getColor() const { return *m_color; }

float Point::getSize() const { return m_size; }

float Point::getX() const { return m_coords.x(); }

float Point::getY() const { return m_coords.y(); }

float Point::getZ() const { return m_coords.z(); }

void Point::setCoords(const QVector3D &newCoords) { m_coords = newCoords; }

void Point::setX(const float &v) { m_coords.setX(v); }

void Point::setY(const float &v) { m_coords.setY(v); }

void Point::setZ(const float &v) { m_coords.setZ(v); }

void Point::setColor(const QColor &color) { *m_color = color; }
