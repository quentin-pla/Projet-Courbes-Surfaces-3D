#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->discretisation_slider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(onUpdateDiscretisation(int)));
    connect(ui->point_show_btn, SIGNAL(toggled(bool)), ui->openGLWidget, SLOT(onShowPoint(bool)));
    connect(ui->polygon_show_btn, SIGNAL(toggled(bool)), ui->openGLWidget, SLOT(onShowControlPoly(bool)));
    connect(ui->u_spin, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(onUpdateUPointCoord(double)));
    connect(ui->v_spin, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(onUpdateVPointCoord(double)));
    connect(ui->views_combo, SIGNAL(currentTextChanged(const QString &)), ui->openGLWidget,
            SLOT(onUpdateSurfaceView(const QString &)));
    connect(ui->openGLWidget, SIGNAL(updateUIPointCoords(Point * )), this, SLOT(onUpdateUIPointCoords(Point * )));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onUpdateUIPointCoords(Point *point) {
    ui->x_value->setText(QString::number(roundf(point->getX() * 1000) / 1000));
    ui->y_value->setText(QString::number(roundf(point->getY() * 1000) / 1000));
    ui->z_value->setText(QString::number(roundf(point->getZ() * 1000) / 1000));
}
