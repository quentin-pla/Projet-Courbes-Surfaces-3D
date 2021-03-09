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

class myOpenGLWidget : public QOpenGLWidget,
			   protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit myOpenGLWidget(QWidget *parent = nullptr);
	~myOpenGLWidget() override;

public slots:

signals:

protected slots:
	void onTimeout();

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent *ev) override;

private:
    /**
     * Angle de vue sur l'axe Y
     */
	double m_angle = 0;

	/**
	 * Timer
	 */
	QTimer *m_timer = nullptr;

	/**
	 * Ratio
	 */
	double m_ratio = 1;

	/**
	 * Radius
	 */
	double m_radius = 0.1;

    /**
     * Distance de la caméra
     */
    double m_distance = 20;

    /**
     * Distance minimale vision scène
     */
    double m_near = 1;

    /**
     * Distance maximale vision scène
     */
    double m_far = 100;

    /**
     * Objets OpenGL
     */
	QVector<GLObject*> objects;

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
     * Initialiser les objets OpenGL
     */
	void makeGLObjects();
};


#endif // MYOPENGLWIDGET_H
