#include "myopenglwidget.h"
#include "segment.h"
#include "courbebezier.h"
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
    m_timer->setInterval(50);  // msec
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
    glClearColor(0, 0, 0, 1);

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
    auto A = new Point(-.5, 0, 0);
    auto B = new Point(.5, 0, 0);
    auto C = new Point(.8, 1, 0);
    auto D = new Point(0, 1.5, 0);

    auto CB = new CourbeBezier({A, B, C, D}, true);

    objects.append(CB);
}

void myOpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    m_ratio = (double) w / h;
}

void myOpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl_funcs = context()->functions();

    m_program->bind();

    resetMatrix();
    GLfloat hr = m_radius, wr = hr * m_ratio;
    proj_mat.frustum(-wr, wr, -hr, hr, m_near, m_far);
    cam_mat.translate(0, 0, -m_distance);
    world_mat.rotate(m_angle, 0, 1, 0);

    for (GLObject *object : objects)
        object->draw(m_program, gl_funcs, world_mat, proj_mat, cam_mat, shape_mat);

    m_program->release();
}

void myOpenGLWidget::resetMatrix() {
    proj_mat.setToIdentity();
    world_mat.setToIdentity();
    cam_mat.setToIdentity();
    shape_mat.setToIdentity();
}

void myOpenGLWidget::keyPressEvent(QKeyEvent *ev) {
    switch (ev->key()) {
        case Qt::Key_Z :
            m_angle += 1;
            if (m_angle >= 360) m_angle -= 360;
            update();
            break;
        case Qt::Key_A :
            if (m_timer->isActive())
                m_timer->stop();
            else m_timer->start();
            break;
        case Qt::Key_R :
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




