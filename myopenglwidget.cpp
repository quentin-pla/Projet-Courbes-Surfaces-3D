#include "myopenglwidget.h"
#include "segment.h"
#include "courbebezier.h"
#include "carreaubezier.h"
#include <QDebug>
#include <QSurfaceFormat>

const QString vertexShaderFile = ":/basic.vsh";
const QString fragmentShaderFile = ":/basic.fsh";

myOpenGLWidget::myOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
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
}

myOpenGLWidget::~myOpenGLWidget() {
    delete m_timer;
    makeCurrent();
    doneCurrent();
}

void myOpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    makeGLObjects();

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFile);
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile);
    if (!m_program->link()) {
        qWarning("Failed to compile and link shader program:");
        qWarning() << m_program->log();
    }
}

void myOpenGLWidget::makeGLObjects() {
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

    auto SB = new CarreauBezier({
        P00, P01, P02, P03,
        P10, P11, P12, P13,
        P20, P21, P22, P23,
        P30, P31, P32, P33
    }, new QColor(Qt::white), true);

    objects.append(SB);
}

void myOpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    m_ratio = (double) w / h;
}

void myOpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl_funcs = context()->functions();
    glClearColor(0, 0, 0, 1);

    m_program->bind();

    resetMatrix();
    GLfloat hr = m_radius, wr = hr * m_ratio;
    proj_mat.frustum(-wr, wr, -hr, hr, m_near, m_far);
    cam_mat.translate(0, 0, -m_distance);
    world_mat.rotate(m_angle_x, 1, 0, 0);
    world_mat.rotate(m_angle_y, 0, 1, 0);

    drawScene();

    m_program->release();
}

void myOpenGLWidget::drawScene() {
    for (GLObject *object : objects) {
        shape_mat = world_mat;
        setTransforms();
        object->draw(m_program, gl_funcs);
    }
}

void myOpenGLWidget::resetMatrix() {
    proj_mat.setToIdentity();
    world_mat.setToIdentity();
    cam_mat.setToIdentity();
    shape_mat.setToIdentity();
}

void myOpenGLWidget::setTransforms() {
    QMatrix4x4 mv_mat = cam_mat * shape_mat;
    m_program->setUniformValue("projMatrix", proj_mat);
    m_program->setUniformValue("mvMatrix", mv_mat);
}

void myOpenGLWidget::keyPressEvent(QKeyEvent *ev) {
    switch (ev->key()) {
        case Qt::Key_Right :
            m_angle_y += 10;
            if (m_angle_y >= 360) m_angle_y -= 360;
            update();
            break;
        case Qt::Key_Left :
            m_angle_y -= 10;
            if (m_angle_y <= 0) m_angle_y += 360;
            update();
            break;
        case Qt::Key_Up :
            m_angle_x += 10;
            if (m_angle_x >= 360) m_angle_x -= 360;
            update();
            break;
        case Qt::Key_Down :
            m_angle_x -= 10;
            if (m_angle_x <= 0) m_angle_x += 360;
            update();
            break;
        case Qt::Key_A :
            if (m_timer->isActive())
                m_timer->stop();
            else m_timer->start();
            break;
    }
}

//void myOpenGLWidget::keyReleaseEvent(QKeyEvent *ev) {}

//void myOpenGLWidget::mousePressEvent(QMouseEvent *ev) {}

//void myOpenGLWidget::mouseReleaseEvent(QMouseEvent *ev) {}

//void myOpenGLWidget::mouseMoveEvent(QMouseEvent *ev) {}

void myOpenGLWidget::onTimeout() {
    update();
}