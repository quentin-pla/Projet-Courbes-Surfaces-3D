#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point.h"

namespace Ui {
    class MainWindow;
}

/**
 * Fenêtre principale
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    /**
     * Constructeur
     * @param parent parent
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * Destructeur
     */
    ~MainWindow() override;

protected slots:

    /**
     * Mettre à jour les coordonnées du point de l'UI
     */
    void onUpdateUIPointCoords(Point *point);

private:
    /**
     * Interface utilisateur
     */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
