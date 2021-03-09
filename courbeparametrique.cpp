#include "courbeparametrique.h"

CourbeParametrique::CourbeParametrique(const QVector<Point *> &points, QColor* color,
                                       const bool &drawControlPolygon) : Discretisation(points) {
    m_drawControlPolygon = drawControlPolygon;
    m_control_points = points;
    for (int i = 0; i < m_control_points.count() - 1; ++i)
        m_control_polygon.append(new Segment(m_control_points[i], m_control_points[i+1], color, true));
}

void CourbeParametrique::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) {
    if (m_drawControlPolygon)
        for (Segment *seg : m_control_polygon)
            seg->draw(program, glFuncs);
    GLObject::draw(program, glFuncs);
}

void CourbeParametrique::showControlPolygon(bool value) {
    m_drawControlPolygon = value;
}
