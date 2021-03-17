#include "carreaubezier.h"

CarreauBezier::CarreauBezier(const QVector<Point *> &points, QColor *color, const bool &drawControlPolygon) {
    m_drawControlPolygon = drawControlPolygon;
    m_control_points = points;
    for (int i = 0; i < m_control_points.count() - 1; ++i) {
        if ((i + 1) % 4)
            m_control_polygon.append(new Segment(m_control_points[i], m_control_points[i + 1], color, true));
        else {
            m_control_polygon.append(new Segment(m_control_points[i], m_control_points[i + 4], color, true));
            m_control_polygon.append(new Segment(m_control_points[i-1], m_control_points[i + 3], color, true));
            m_control_polygon.append(new Segment(m_control_points[i-2], m_control_points[i + 2], color, true));
            m_control_polygon.append(new Segment(m_control_points[i-3], m_control_points[i + 1], color, true));
        }
    }

    if (m_drawControlPolygon) {
        for (Segment *seg : m_control_polygon) {
            for (Point *point : seg->generateStepPoints(0.1, color)) {
                point->setColor(QColor(150,150,150));
                vertices.append(point->getCoords());
                colors.append(point->getColor());
            }
            addVBO(GL_LINES);
        }
    }
}

void CarreauBezier::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) {
    if (m_drawControlPolygon) {
        for (Segment *seg : m_control_polygon) {
            Point* start = seg->getStart();
            Point* end = seg->getEnd();
            QColor color(150,150,150);
            start->setColor(color);
            end->setColor(color);
            start->draw(program, glFuncs);
            end->draw(program, glFuncs);
        }
    }
    glLineWidth(3);
    GLObject::draw(program, glFuncs);
}

void CarreauBezier::showControlPolygon(bool value) {
    m_drawControlPolygon = value;
}