#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H

#include "courbeparametrique.h"
#include "segment.h"

class CourbeBezier : public CourbeParametrique {
public:
    /**
     * Constructeur
     * @param points points de controle
     * @param drawControlPolygon afficher le polygone de controle
     */
    explicit CourbeBezier(const QVector<Point*> &points, const bool &drawControlPolygon = false);
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
     * Obtenir le point à une certaine valeur
     * @param color couleur du point
     * @return point
     */
    Point* getPoint(float value) const override;
};


#endif //COURBEBEZIER_H
