#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QObject>
#include <QWidget>

#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "globject.h"
#include "point.h"
#include "carreaubeziercubique.h"

/**
 * Widget OpenGL
 */
class GLArea : public QOpenGLWidget,
               protected QOpenGLFunctions {
Q_OBJECT

public:
    /**
     * Constructeur
     * @param parent parent
     */
    explicit GLArea(QWidget *parent = nullptr);

    /**
     * Destructeur
     */
    ~GLArea() override;

signals:

    /**
     * Mettre à jour les coordonnées du point dans l'UI
     * @param point nouveau point
     */
    void updateUIPointCoords(Point *point);

protected slots:

    /**
     * Lorsque le timer est écoulé
     */
    void onTimeout();

    /**
     * Affichage du polyèdre de contrôle
     * @param value valeur
     */
    void onShowControlPoly(bool value);

    /**
     * Afficher le point sur la surface
     * @param value valeur
     */
    void onShowPoint(bool value);

    /**
     * Lorsque la coordonnée U du point a été mise à jour
     * @param u U
     */
    void onUpdateUPointCoord(double u);

    /**
     * Lorsque la coordonnée V du point a été mise à jour
     * @param v V
     */
    void onUpdateVPointCoord(double v);

    /**
     * Lorsque la valeur de la discrétisation est mise à jour
     * @param value valeur
     */
    void onUpdateDiscretisation(int value);

    /**
     * Lorsque la valeur de l'affichage de la surface est modifiée
     * @param value valeur
     */
    void onUpdateSurfaceView(const QString &);

    /**
     * Définir la valeur de l'angle de vue X
     * @param value valeur
     */
    void setXAngle(int value);

    /**
     * Définir la valeur de l'angle de vue Y
     * @param value
     */
    void setYAngle(int value);

private:
    // PARAMÈTRES SCÈNE //

    /**
     * Angle de vue sur l'axe X
     */
    float m_angle_x = 0;

    /**
     * Angle de vue sur l'axe Y
     */
    float m_angle_y = 0;

    /**
     * Timer
     */
    QTimer *m_timer = nullptr;

    /**
     * Ratio
     */
    float m_ratio = 1;

    /**
     * Radius
     */
    float m_radius = 0.1;

    /**
     * Distance de la caméra
     */
    float m_distance = 15;

    /**
     * Distance minimale vision scène
     */
    float m_near = 1;

    /**
     * Distance maximale vision scène
     */
    float m_far = 100;

    /**
     * Dernière position enregistrée de la souris
     */
    QPoint *last_mouse_pos = nullptr;

    /**
     * Objets OpenGL
     */
    QVector<GLObject *> gl_objects;

    /**
     * Carreau de bézier cubique
     */
    CarreauBezierCubique *bezier_tile;

    /**
     * Matrice de projection
     */
    QMatrix4x4 proj_mat;

    /**
     * Matrice du monde
     */
    QMatrix4x4 world_mat;

    /**
     * Matrice de la caméra
     */
    QMatrix4x4 cam_mat;

    /**
     * Matrice de transformation objets
     */
    QMatrix4x4 shape_mat;

    /**
     * Matrice des normales
     */
    QMatrix3x3 normal_mat;

    /**
     * Programme OpenGL
     */
    QOpenGLShaderProgram *m_program;

    /**
     * Fonctions OpenGL
     */
    QOpenGLFunctions *gl_funcs;

    /**
     * Réinitialiser les matrices
     */
    void resetMatrix();

    /**
     * Appliquer les transformations
     */
    void setTransforms();

    /**
     * Initialiser les objets OpenGL
     */
    void makeGLObjects();

    /**
     * Dessiner la scène
     */
    void drawScene();

    // PARAMÈTRES INTERFACE GRAPHIQUE //

    /**
     * Affichage du polyèdre de contrôle
     */
    bool m_show_control_poly = false;

    /**
     * Affichage du point sur la surface
     */
    bool m_show_point = false;

    /**
     * Discrétisation de la surface
     */
    float m_discretisation = 0.1f;

    /**
     * Point affiché sur la surface
     */
    Point *m_surface_point = nullptr;

    float m_u_value;

    float m_v_value;

protected:

    // OVERRIDE //

    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *ev) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MYOPENGLWIDGET_H
