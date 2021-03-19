#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sstream"
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->discretisation_spin, SIGNAL(valueChanged(double)), ui->openGLWidget,
            SLOT(onUpdateDiscretisation(double)));
    connect(ui->point_show_btn, SIGNAL(toggled(bool)), ui->openGLWidget, SLOT(onShowPoint(bool)));
    connect(ui->polygon_show_btn, SIGNAL(toggled(bool)), ui->openGLWidget, SLOT(onShowControlPoly(bool)));
    connect(ui->u_spin, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(onUpdateUPointCoord(double)));
    connect(ui->v_spin, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(onUpdateVPointCoord(double)));
    connect(ui->views_combo, SIGNAL(currentTextChanged(const QString &)), ui->openGLWidget,
            SLOT(onUpdateSurfaceView(const QString &)));
    connect(ui->openGLWidget, SIGNAL(updateUIPointCoords(Point * )), this, SLOT(onUpdateUIPointCoords(Point * )));
    connect(ui->random_tile_btn, SIGNAL(pressed()), ui->openGLWidget, SLOT(onGenerateNewTile()));
    connect(ui->generate_obj_btn, SIGNAL(pressed()), ui->openGLWidget, SLOT(onGenerateOBJFile()));
    connect(ui->openGLWidget, SIGNAL(saveOBJFile(const std::stringstream &)), this,
            SLOT(onSaveOBJFile(const std::stringstream &)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onUpdateUIPointCoords(Point *point) {
    ui->x_value->setText(QString::number(roundf(point->getX() * 1000) / 1000));
    ui->y_value->setText(QString::number(roundf(point->getY() * 1000) / 1000));
    ui->z_value->setText(QString::number(roundf(point->getZ() * 1000) / 1000));
}

void MainWindow::onSaveOBJFile(const std::stringstream &data) {
    auto string_data = new QString(data.str().c_str());
    // Attente de 200ms sinon bug interface bouton qui reste enclenché
    QTimer::singleShot(200, [string_data] {
        QString file_name = QFileDialog::getSaveFileName(nullptr, "Sauvegarder la surface",
                                                         "carreau_bezier", "Fichier OBJ (*.obj);");
        if (file_name.isEmpty()) return;
        else {
            if (!file_name.contains("."))
                file_name.append(".obj");
            QFile tile_file(file_name);
            QFile controls_file(file_name.mid(0, file_name.indexOf('.')) + "_controls.obj");
            if (!tile_file.open(QIODevice::WriteOnly) || !controls_file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(nullptr, tr("Écriture dans le fichier impossible."), tile_file.errorString());
                return;
            }
            QTextStream tile_out(&tile_file);
            tile_out.setCodec("UTF-8");
            tile_out.setGenerateByteOrderMark(false);
            tile_out << string_data->mid(0, string_data->indexOf("o controls"));
            tile_file.close();
            QTextStream controls_out(&controls_file);
            controls_out.setCodec("UTF-8");
            controls_out.setGenerateByteOrderMark(false);
            controls_out << string_data->mid(string_data->indexOf("o controls"));
            controls_file.close();
        }
    });
}
