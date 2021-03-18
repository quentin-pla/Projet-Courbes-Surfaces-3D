#include "courbebezier.h"

CourbeBezier::CourbeBezier(const QVector<Point*> &points, QColor* color,
                           const bool &drawControlPolygon) : CourbeParametrique(points, color, drawControlPolygon) {
}

Point *CourbeBezier::getValue(float pos, QColor* color) const {
    QVector<Segment*> sub_segments;
    sub_segments = m_control_polygon;
    while (sub_segments.count() > 1) {
        QVector<Segment*> child_segments;
        for (int i = 0; i < sub_segments.count() - 1; ++i)
            child_segments.push_back(new Segment(sub_segments[i]->getValue(pos), sub_segments[i + 1]->getValue(pos)));
        sub_segments = child_segments;
    }
    return sub_segments.first()->getValue(pos, color);
}

void CourbeBezier::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) {
    CourbeParametrique::draw(program, glFuncs);
}

void CourbeBezier::render() {
    for (Point *point : generateStepPoints(0.05, m_color)) {
        vertices.push_back(point->getCoords());
        colors.push_back(point->getColor());
        normals.push_back(point->getCoords());
    }
    addVBO(GL_LINE_STRIP);

    CourbeParametrique::render();
}
