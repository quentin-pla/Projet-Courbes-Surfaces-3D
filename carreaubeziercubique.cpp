#include "carreaubeziercubique.h"

CarreauBezierCubique::CarreauBezierCubique(const QVector<Point *> &points, QColor *color,
                                           const bool &drawControlPolygon) : Discretisation(points) {
    m_drawControlPolygon = drawControlPolygon;
    m_control_points = points;
    m_color = color;

    // Polygone de controle
    for (int i = 0; i < m_control_points.count() - 1; i += 4) {
        m_control_polygon.append(new Segment(m_control_points[i], m_control_points[i + 1], m_color, true));
        m_control_polygon.append(new Segment(m_control_points[i + 1], m_control_points[i + 2], m_color, true));
        m_control_polygon.append(new Segment(m_control_points[i + 2], m_control_points[i + 3], m_color, true));
    }
    for (int i = 0; i < 4; ++i) {
        m_control_polygon.append(new Segment(m_control_points[i], m_control_points[i + 4], m_color, true));
        m_control_polygon.append(new Segment(m_control_points[i + 4], m_control_points[i + 8], m_color, true));
        m_control_polygon.append(new Segment(m_control_points[i + 8], m_control_points[i + 12], m_color, true));
    }

    // Courbes de bézier utilisées pour récupérer la valeur d'un point
    for (int i = 0; i < m_control_points.count(); i += 4) {
        QVector<Point *> curve_points;
        for (int j = i; j < i + 4; ++j)
            curve_points.append(m_control_points[j]);
        m_bezier_curves.append(new CourbeBezier(curve_points, m_color));
    }
}

void CarreauBezierCubique::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) {
    GLObject::draw(program, glFuncs);
//    if (m_drawControlPolygon) {
//        for (Segment *seg : m_control_polygon) {
//            Point *start = seg->getStart();
//            Point *end = seg->getEnd();
//            QColor color(150, 150, 150);
//            start->setColor(color);
//            end->setColor(color);
//            start->draw(program, glFuncs);
//            end->draw(program, glFuncs);
//            for (Point *point : seg->generateStepPoints(0.1)) {
//                point->setColor(color);
//                point->draw(program, glFuncs);
//            }
//        }
//    }
}

Point *CarreauBezierCubique::getValue(float x, float y, QColor *color) const {
    QVector<Segment *> sub_segments;
    for (int i = 0; i < m_bezier_curves.count() - 1; ++i) {
        Point *start = m_bezier_curves[i]->getValue(x);
        Point *end = m_bezier_curves[i + 1]->getValue(x);
        sub_segments.append(new Segment(start, end));
    }
    while (sub_segments.count() > 1) {
        QVector<Segment *> child_segments;
        for (int i = 0; i < sub_segments.count() - 1; ++i)
            child_segments.push_back(new Segment(sub_segments[i]->getValue(y), sub_segments[i + 1]->getValue(y)));
        sub_segments = child_segments;
    }
    return sub_segments.first()->getValue(y, color);
}

void CarreauBezierCubique::showControlPolygon(bool value) {
    m_drawControlPolygon = value;
}

void CarreauBezierCubique::render() {
    for (float y = 0; y < 1; y += .1f) {
        for (float x = 0; x <= 1.1; x += .1f) {
            Point *point = getValue(x, y, m_color);
            vertices.append(point->getCoords());
            colors.append(point->getColor());
            normals.append(point->getCoords());
            point = getValue(x, y + .1f, m_color);
            vertices.append(point->getCoords());
            colors.append(point->getColor());
            normals.append(point->getCoords());
        }
        addVBO(GL_QUAD_STRIP);
    }
    GLObject::render();
}
