#include "glarea.h"
#include "segment.h"
#include "carreaubeziercubique.h"
#include <QDebug>

GLArea::GLArea(QWidget *parent) : QOpenGLWidget(parent) {
    QSurfaceFormat sf;
    sf.setDepthBufferSize(24);
    sf.setSamples(16);
    setFormat(sf);

    setEnabled(true);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    m_timer = new QTimer(this);
    m_timer->setInterval(50);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    this->setCursor(QCursor(Qt::OpenHandCursor));
}

GLArea::~GLArea() {
    delete m_timer;
    delete m_bezier_tile;
    delete m_surface_point;
    makeCurrent();
    doneCurrent();
}

void GLArea::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearColor(0, 0, 0, 1);

    makeGLObjects();

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment.glsl");
    if (!m_program->link()) {
        qWarning("Failed to compile and link shader program:");
        qWarning() << m_program->log();
    }
}

CarreauBezierCubique *GLArea::generateRandomBezierTile() {
    if (m_tile_random_points.isEmpty()) {
        float min = -0.8f;
        float max = 0.8f;
        float step = 0.4f;

        for (float z = min; z <= max; z += step) {
            for (float y = min; y <= max; y += step) {
                for (float x = min; x <= max; x += step) {
                    m_tile_random_points.append(new Point(x, y, z));
                }
            }
        }
    }

    QVector<Point *> tile_points;

    for (int i = 0; i < 16; ++i) {
        Point *point = m_tile_random_points[rand() % m_tile_random_points.count()];
        while (tile_points.contains(point))
            point = m_tile_random_points[rand() % m_tile_random_points.count()];
        tile_points.append(point);
    }

    QVector<QColor> available_colors = {Qt::white, Qt::green, Qt::blue, Qt::yellow, Qt::magenta, Qt::cyan};

    return new CarreauBezierCubique(tile_points, available_colors[rand() % available_colors.count()],
                                    m_draw_bezier_tile_poly, m_draw_mode, m_discretisation_step);
}

void GLArea::makeGLObjects() {
    // Carreau par défaut

    auto P00 = new Point(-.8, -.3, .6);
    auto P01 = new Point(-.3, 0, .6);
    auto P02 = new Point(.3, 0, .6);
    auto P03 = new Point(.8, -.3, .6);

    auto P10 = new Point(-.8, -.3, 0);
    auto P11 = new Point(-.3, 0, 0);
    auto P12 = new Point(.3, 0, 0);
    auto P13 = new Point(.8, -.3, 0);

    auto P20 = new Point(-.8, -.3, -.6);
    auto P21 = new Point(-.3, 0, -.6);
    auto P22 = new Point(.3, 0, -.6);
    auto P23 = new Point(.8, -.3, -.6);

    auto P30 = new Point(-.8, .2, -.6);
    auto P31 = new Point(-.3, .4, -.6);
    auto P32 = new Point(.3, .4, -.6);
    auto P33 = new Point(.8, .2, -.6);

    m_bezier_tile = new CarreauBezierCubique(
            {
                    P00, P01, P02, P03,
                    P10, P11, P12, P13,
                    P20, P21, P22, P23,
                    P30, P31, P32, P33
            }, Qt::green
    );

    m_surface_point = new Point(Qt::red, 20);
    m_surface_point->render();
    m_surface_point->setCoords(m_bezier_tile->getValue(m_u_value, m_v_value)->getCoords());
    emit updateUIPointCoords(m_surface_point);
}

void GLArea::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    m_ratio = w / h;
}

void GLArea::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl_funcs = context()->functions();
    glClearColor(0, 0, 0, 1);

    m_program->bind();

    resetMatrix();

    GLfloat hr = m_radius, wr = hr * m_ratio;
    proj_mat.frustum(-wr, wr, -hr, hr, m_near, m_far);
    cam_mat.translate(0, 0, -m_distance);

    drawScene();

    m_program->release();
}

void GLArea::drawScene() {
    if (m_bezier_tile != nullptr) {
        shape_mat = world_mat;
        shape_mat.rotate(m_angle_x, 1, 0, 0);
        shape_mat.rotate(m_angle_y, 0, 1, 0);
        setTransforms();
        m_bezier_tile->draw(m_program, gl_funcs);
    }
    if (m_surface_point != nullptr && m_show_point) {
        shape_mat = world_mat;
        shape_mat.rotate(m_angle_x, 1, 0, 0);
        shape_mat.rotate(m_angle_y, 0, 1, 0);
        shape_mat.translate(m_surface_point->getCoords());
        setTransforms();
        m_surface_point->draw(m_program, gl_funcs);
    }
}

void GLArea::resetMatrix() {
    proj_mat.setToIdentity();
    world_mat.setToIdentity();
    cam_mat.setToIdentity();
    shape_mat.setToIdentity();
}

void GLArea::setTransforms() {
    QMatrix4x4 mv_mat = cam_mat * shape_mat;
    normal_mat = shape_mat.normalMatrix();
    m_program->setUniformValue("projMatrix", proj_mat);
    m_program->setUniformValue("mvMatrix", mv_mat);
    m_program->setUniformValue("norMatrix", normal_mat);
}

void GLArea::keyPressEvent(QKeyEvent *ev) {
    //
}

void GLArea::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        if (last_mouse_pos != nullptr) {
            int drag_x = event->x() - last_mouse_pos->x();
            int drag_y = event->y() - last_mouse_pos->y();
            setXAngle(drag_y);
            setYAngle(drag_x);
            update();
        }
        last_mouse_pos = new QPoint(event->pos());
    }
}

void GLArea::mousePressEvent(QMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));
}

void GLArea::mouseReleaseEvent(QMouseEvent *event) {
    last_mouse_pos = nullptr;
    this->setCursor(QCursor(Qt::OpenHandCursor));
}

void GLArea::onTimeout() {
    update();
}

void GLArea::setXAngle(int value) {
    m_angle_x += (float) value;
    if (m_angle_x >= 360) m_angle_x -= 360;
    else if (m_angle_x <= 0) m_angle_x += 360;
}

void GLArea::setYAngle(int value) {
    m_angle_y += (float) value;
    if (m_angle_y >= 360) m_angle_y -= 360;
    else if (m_angle_y <= 0) m_angle_y += 360;
}

void GLArea::onShowControlPoly(bool value) {
    m_draw_bezier_tile_poly = value;
    m_bezier_tile->showControlPolygon(m_draw_bezier_tile_poly);
    update();
}

void GLArea::onShowPoint(bool value) {
    m_show_point = value;
    update();
}

void GLArea::onUpdateDiscretisation(double value) {
    m_discretisation_step = (float) value;
    m_bezier_tile->setDiscretisationStep(m_discretisation_step);
    update();
}

void GLArea::onUpdateUPointCoord(double u) {
    m_u_value = (float) u;
    m_surface_point->setCoords(m_bezier_tile->getValue(m_u_value, m_v_value)->getCoords());
    emit updateUIPointCoords(m_surface_point);
    update();
}

void GLArea::onUpdateVPointCoord(double v) {
    m_v_value = (float) v;
    m_surface_point->setCoords(m_bezier_tile->getValue(m_u_value, m_v_value)->getCoords());
    emit updateUIPointCoords(m_surface_point);
    update();
}

void GLArea::onUpdateSurfaceView(const QString &value) {
    if (value == "Pleine")
        m_draw_mode = GL_TRIANGLES;
    else if (value == "Filaire")
        m_draw_mode = GL_LINE_LOOP;
    else if (value == "Points")
        m_draw_mode = GL_POINTS;
    m_bezier_tile->setDrawMode(m_draw_mode);
    update();
}

void GLArea::onGenerateNewTile() {
    delete m_bezier_tile;
    m_bezier_tile = generateRandomBezierTile();
    m_surface_point->setCoords(m_bezier_tile->getValue(m_u_value, m_v_value)->getCoords());
    emit updateUIPointCoords(m_surface_point);
    update();
}
