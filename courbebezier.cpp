#include "courbebezier.h"

CourbeBezier::CourbeBezier(const QVector<Point*> &points,
                           const bool &drawControlPolygon) : CourbeParametrique(points, drawControlPolygon) {
    QVector<Point*> curve_points = generateStepPoints(0.05, new QColor(Qt::red));
    for (int i = 0; i < curve_points.count() - 1; ++i)
        m_curve.push_back(new Segment(curve_points[i], curve_points[i+1], false));
}

Point *CourbeBezier::getValue(float pos, const QColor &color) const {
    QVector<Segment*> sub_segments;
    sub_segments = m_control_polygon;
    while (sub_segments.count() > 1) {
        QVector<Segment*> child_segments;
        for (int i = 0; i < sub_segments.count() - 1; ++i)
            child_segments.push_back(new Segment(sub_segments[i]->getValue(pos, color),
                                                 sub_segments[i+1]->getValue(pos, color)));
        sub_segments = child_segments;
    }
    return sub_segments.first()->getValue(pos, color);
}

void CourbeBezier::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs, QMatrix4x4 &world_mat,
                              QMatrix4x4 &proj_mat, QMatrix4x4 &cam_mat, QMatrix4x4 &shape_mat) {
    for (Segment* segment : m_curve)
        segment->draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
    CourbeParametrique::draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
}
