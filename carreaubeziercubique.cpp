#include <sstream>
#include "carreaubeziercubique.h"

CarreauBezierCubique::CarreauBezierCubique(const QVector<Point *> &points, const QColor &color,
                                           const bool &drawControlPolygon, const unsigned char &drawMode,
                                           const float &discretisationStep) : Discretisation(points) {
    m_drawControlPolygon = drawControlPolygon;
    m_control_points = points;
    m_color = color;
    m_draw_mode = drawMode;
    m_discretisation_step = discretisationStep;

    // Courbes de bézier utilisées pour récupérer la valeur d'un point

    for (int i = 0; i < m_control_points.count(); i += 4) {
        QVector<Point *> curve_points;
        for (int j = i; j < i + 4; ++j)
            curve_points.append(m_control_points[j]);
        m_bezier_curves.append(new CourbeBezier(curve_points, m_color));
    }

    // Génération des segments de contrôle

    QColor segments_color(Qt::white);

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

    render();
}

CarreauBezierCubique::~CarreauBezierCubique() {
    GLObject::~GLObject();
}

void CarreauBezierCubique::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                                const QVector<unsigned char> &drawTypes_override) {
    glEnable(GL_DEPTH_TEST);
    // Affichage triangles recouvrants la surface
    for (Polygon *triangle : m_surface_triangles) {
        triangle->setLineWidth((int) ((m_discretisation_step * 100) / 2.5));
        glPointSize((int) ((m_discretisation_step * 100) / 2));
        triangle->draw(program, glFuncs, {m_draw_mode});
    }
    glDisable(GL_DEPTH_TEST);
    // Affichage segments de contrôle
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
    // Génération de la surface du carreau

    m_surface_triangles.clear();
    m_points.clear();

    for (float y = 0; y < 1; y += m_discretisation_step) {
        for (float x = 0; x < 1; x += m_discretisation_step) {
            QVector<Point *> points;
            points.append(getValue(x, y, m_color));
            points.append(getValue(x, y + m_discretisation_step, m_color));
            points.append(getValue(x + m_discretisation_step, y, m_color));
            points.append(getValue(x + m_discretisation_step, y + m_discretisation_step, m_color));
            m_surface_triangles.append(new Polygon({points[0], points[1], points[2]}, m_color));
            m_surface_triangles.append(new Polygon({points[2], points[3], points[1]}, m_color));
            m_points.append(points);
        }
    }

    for (Polygon *triangle : m_surface_triangles)
        triangle->enablePointsNormals(true);

    GLObject::render();
}

void CarreauBezierCubique::setDrawMode(unsigned char draw_mode) {
    m_draw_mode = draw_mode;
}

void CarreauBezierCubique::setDiscretisationStep(float value) {
    m_discretisation_step = value;
    render();
}

std::stringstream CarreauBezierCubique::generateOBJFile() const {
    QVector<QString> obj_points;
    for (Point *point : m_points)
        obj_points.append(QString::number(point->getX()) + " " +
                          QString::number(point->getY()) + " " +
                          QString::number(point->getZ()));
    std::stringstream data;
    data << "o surface_bezier" << std::endl << std::endl;

    // Sommets
    for (const QString &point : obj_points)
        data << "v " << point.toStdString() << std::endl;
    data << std::endl;

    // Normales
    for (const QString &point : obj_points)
        data << "vn " << point.toStdString() << std::endl;
    data << std::endl;

    // Faces
    for (int i = 0; i < obj_points.count() - 3; i += 4) {
        int p0 = i + 1;
        int p1 = i + 2;
        int p2 = i + 3;
        int p3 = i + 4;

        // Premier triangle (face avant)
        data << "f ";
        data << p2 << "//" << p2 << " ";
        data << p1 << "//" << p1 << " ";
        data << p0 << "//" << p0 << std::endl;

        // Premier triangle (face arrière)
        data << "f ";
        data << p0 << "//" << p0 << " ";
        data << p1 << "//" << p1 << " ";
        data << p2 << "//" << p2 << std::endl;

        // Deuxième triangle (face avant)
        data << "f ";
        data << p2 << "//" << p2 << " ";
        data << p3 << "//" << p3 << " ";
        data << p1 << "//" << p1 << std::endl;

        // Deuxième triangle (face arrière)
        data << "f ";
        data << p1 << "//" << p1 << " ";
        data << p3 << "//" << p3 << " ";
        data << p2 << "//" << p2 << std::endl;
    }
    return data;
}
