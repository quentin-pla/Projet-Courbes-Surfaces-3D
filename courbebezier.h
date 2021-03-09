#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H

#include "courbeparametrique.h"

class CourbeBezier : public CourbeParametrique {
public:
    /**
     * Constructeur
     * @param points points de controle
     * @param drawControlPolygon afficher le polygone de controle
     */
    explicit CourbeBezier(const QVector<Point*> &points, const bool &drawControlPolygon = false);

    /**
     * Destructeur
     */
    ~CourbeBezier() = default;

    /**
     * Dessiner la courbe
     * @param program programme
     * @param glFuncs fonctions OpenGL
     * @param world_mat matrice du monde
     * @param proj_mat matrice de projection
     * @param cam_mat matrice caméra
     * @param shape_mat matrice de transformation
     */
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
              QMatrix4x4& world_mat, QMatrix4x4& proj_mat, QMatrix4x4& cam_mat, QMatrix4x4& shape_mat) override;

    /**
     * Obtenir un point à une position spécifique
     * @param pos position
     * @return point
     */
    Point* getValue(float pos, const QColor &color) const override;
};


#endif //COURBEBEZIER_H
