#include "courbeparametrique.h"

CourbeParametrique::CourbeParametrique(const QVector<Point *> &points, const bool &drawControlPolygon) : Discretisation(points) {
    m_drawControlPolygon = drawControlPolygon;
    m_control_points = points;
    for (int i = 0; i < m_control_points.count() - 1; ++i)
        m_control_polygon.append(new Segment(m_control_points[i], m_control_points[i+1], true));
}

void CourbeParametrique::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs, QMatrix4x4 &world_mat,
                              QMatrix4x4 &proj_mat, QMatrix4x4 &cam_mat, QMatrix4x4 &shape_mat) {
    if (m_drawControlPolygon)
        for (Segment *seg : m_control_polygon)
            seg->draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
    GLObject::draw(program, glFuncs, world_mat, proj_mat, cam_mat, shape_mat);
}

void CourbeParametrique::showControlPolygon(bool value) {
    m_drawControlPolygon = value;
}
