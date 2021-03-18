#include "courbeparametrique.h"

CourbeParametrique::CourbeParametrique(const QVector<Point *> &points, const QColor &color,
                                       const bool &drawControlPolygon) : Discretisation(points) {
    m_drawControlPolygon = drawControlPolygon;
    m_control_points = points;
    m_color = color;

    for (int i = 0; i < m_control_points.count() - 1; ++i)
        m_control_polygon.append(new Segment(m_control_points[i], m_control_points[i + 1], m_color, true));
}

void CourbeParametrique::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                              const QVector<unsigned char> &drawTypes_override) {
    if (m_drawControlPolygon) {
        for (Segment *seg : m_control_polygon) {
            Point *start = seg->getStart();
            Point *end = seg->getEnd();
            QColor color(150, 150, 150);
            start->setColor(color);
            end->setColor(color);
            start->draw(program, glFuncs);
            end->draw(program, glFuncs);
        }
    }
    glLineWidth(3);
    GLObject::draw(program, glFuncs);
}

void CourbeParametrique::showControlPolygon(bool value) {
    m_drawControlPolygon = value;
}

void CourbeParametrique::render() {
    if (m_drawControlPolygon) {
        for (Segment *seg : m_control_polygon) {
            for (Point *point : seg->generateStepPoints(0.1, m_color)) {
                point->setColor(QColor(150, 150, 150));
                m_vertices.append(point->getCoords());
                m_colors.append(point->getColor());
                m_normals.append(point->getCoords());
            }
        }
        addVBO(GL_LINES);
    }

    GLObject::render();
}
