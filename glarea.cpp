#include "glarea.h"
#include "segment.h"
#include "courbebezier.h"
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

void GLArea::makeGLObjects() {
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

    auto SB = new CarreauBezierCubique({
                                               P00, P01, P02, P03,
                                               P10, P11, P12, P13,
                                               P20, P21, P22, P23,
                                               P30, P31, P32, P33
                                       }, Qt::green);

    bezier_tile = SB;

    gl_objects.append(SB);

    m_surface_point = new Point(Qt::red, 20);
    m_surface_point->render();
    m_surface_point->setCoords(bezier_tile->getValue(m_u_value, m_v_value)->getCoords());
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
    for (GLObject *object : gl_objects) {
        shape_mat = world_mat;
        shape_mat.rotate(m_angle_x, 1, 0, 0);
        shape_mat.rotate(m_angle_y, 0, 1, 0);
        setTransforms();
        object->draw(m_program, gl_funcs);
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
    m_show_control_poly = value;
    bezier_tile->showControlPolygon(value);
    update();
}

void GLArea::onShowPoint(bool value) {
    m_show_point = value;
    update();
}

void GLArea::onUpdateDiscretisation(int value) {
    m_discretisation = (float) value;
    update();
}

void GLArea::onUpdateUPointCoord(double u) {
    m_u_value = (float) u;
    m_surface_point->setCoords(bezier_tile->getValue(m_u_value, m_v_value)->getCoords());
    emit updateUIPointCoords(m_surface_point);
    update();
}

void GLArea::onUpdateVPointCoord(double v) {
    m_v_value = (float) v;
    m_surface_point->setCoords(bezier_tile->getValue(m_u_value, m_v_value)->getCoords());
    emit updateUIPointCoords(m_surface_point);
    update();
}

void GLArea::onUpdateSurfaceView(const QString &value) {
    //
}
