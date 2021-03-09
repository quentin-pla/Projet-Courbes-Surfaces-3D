
#include "courbebezier.h"

CourbeBezier::CourbeBezier(const QVector<Point*> &points,
                           const bool &drawControlPolygon) : CourbeParametrique(points, drawControlPolygon) {

}

Point *CourbeBezier::getPoint(float value) const {
    QVector<Segment*> sub_segments;
    sub_segments = m_control_polygon;
    while (sub_segments.count() > 1) {
        QVector<Segment*> child_segments;
        for (int i = 0; i < sub_segments.count() - 1; ++i)
            child_segments.push_back(new Segment(sub_segments[i]->getPoint(value),sub_segments[i+1]->getPoint(value)));
        sub_segments = child_segments;
    }
    return sub_segments[0]->getPoint(value);
}

void CourbeBezier::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs, QMatrix4x4 &world_mat,
                              QMatrix4x4 &proj_mat, QMatrix4x4 &cam_mat, QMatrix4x4 &shape_mat) {
    CourbeParametrique::draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
    getPoint(0.2)->draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
    getPoint(0.4)->draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
    getPoint(0.6)->draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
    getPoint(0.8)->draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
}
