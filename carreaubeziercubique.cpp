#include "carreaubeziercubique.h"

CarreauBezierCubique::CarreauBezierCubique(const QVector<Point *> &points, const QColor &color,
                                           const bool &drawControlPolygon) : Discretisation(points) {
    m_drawControlPolygon = drawControlPolygon;
    m_control_points = points;
    m_color = color;
    m_draw_mode = GL_TRIANGLES;
    vbos_count = 0;

    // Courbes de bézier utilisées pour récupérer la valeur d'un point
    for (int i = 0; i < m_control_points.count(); i += 4) {
        QVector<Point *> curve_points;
        for (int j = i; j < i + 4; ++j)
            curve_points.append(m_control_points[j]);
        m_bezier_curves.append(new CourbeBezier(curve_points, m_color));
    }
}

void CarreauBezierCubique::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                                const QVector<unsigned char> &drawTypes_override) {
    QVector<unsigned char> draw_modes;
    if (m_draw_mode != GL_TRIANGLES)
        draw_modes.insert(0, vbos_count, m_draw_mode);
    GLObject::draw(program, glFuncs, draw_modes);
    if (m_drawControlPolygon) {
        for (Segment *segment : m_control_segments)
            segment->draw(program, glFuncs);
    }
}

Point *CarreauBezierCubique::getValue(float x, float y, const QColor &color) const {
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
    // Génération de la surface pleine
    for (float y = 0; y < 1; y += .1f) {
        for (float x = 0; x <= 1; x += .1f) {
            Point *point = getValue(x, y, m_color);
            m_vertices.append(point->getCoords());
            m_colors.append(point->getColor());
            m_normals.append(point->getCoords());
            point = getValue(x, y + .1f, m_color);
            m_vertices.append(point->getCoords());
            m_colors.append(point->getColor());
            m_normals.append(point->getCoords());
            point = getValue(x + .1f, y, m_color);
            m_vertices.append(point->getCoords());
            m_colors.append(point->getColor());
            m_normals.append(point->getCoords());
            addVBO(GL_TRIANGLES);
            m_vertices.append(point->getCoords());
            m_colors.append(point->getColor());
            m_normals.append(point->getCoords());
            point = getValue(x + .1f, y + .1f, m_color);
            m_vertices.append(point->getCoords());
            m_colors.append(point->getColor());
            m_normals.append(point->getCoords());
            point = getValue(x, y + .1f, m_color);
            m_vertices.append(point->getCoords());
            m_colors.append(point->getColor());
            m_normals.append(point->getCoords());
            addVBO(GL_TRIANGLES);
            vbos_count += 2;
        }
    }

//    for (float y = 0; y < 1; y += .1f) {
//        for (float x = 0; x <= 1.1; x += .1f) {
//            Point *point = getValue(x, y, m_color);
//            m_vertices.append(point->getCoords());
//            m_colors.append(point->getColor());
//            m_normals.append(point->getCoords());
//            point = getValue(x, y + .1f, m_color);
//            m_vertices.append(point->getCoords());
//            m_colors.append(point->getColor());
//            m_normals.append(point->getCoords());
//        }
//        addVBO(GL_TRIANGLE_STRIP);
//    }

    // Génération des segments de contrôle

    QColor segments_color(150, 150, 150);

    for (int i = 0; i < m_control_points.count() - 1; i += 4) {
        m_control_segments.append(new Segment(m_control_points[i], m_control_points[i + 1], segments_color, true));
        m_control_segments.append(new Segment(m_control_points[i + 1], m_control_points[i + 2], segments_color, true));
        m_control_segments.append(new Segment(m_control_points[i + 2], m_control_points[i + 3], segments_color, true));
    }
    for (int i = 0; i < 4; ++i) {
        m_control_segments.append(new Segment(m_control_points[i], m_control_points[i + 4], segments_color, true));
        m_control_segments.append(new Segment(m_control_points[i + 4], m_control_points[i + 8], segments_color, true));
        m_control_segments.append(new Segment(m_control_points[i + 8], m_control_points[i + 12], segments_color, true));
    }

    GLObject::render();
}