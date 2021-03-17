#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    /**
     * Interface utilisateur
     */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
