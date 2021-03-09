#ifndef COURBEPARAMETRIQUE_H
#define COURBEPARAMETRIQUE_H

#include "discretisation.h"
#include "segment.h"

/**
 * Courbe paramétrique
 */
class CourbeParametrique : public GLObject, public Discretisation {
private:
    /**
     * Dessiner le polygone de controle
     */
    bool m_drawControlPolygon;

protected:
    /**
     * Constructeur
     * @param points liste des points de la courbe
     */
    explicit CourbeParametrique(const QVector<Point*> &points, const bool &drawControlPolygon = false);

    /**
     * Destructeur
     */
    ~CourbeParametrique() = default;

    /**
     * Liste des points de controle
     */
    QVector<Point*> m_control_points;

    /**
     * Liste des segments formant la courbe
     */
    QVector<Segment*> m_curve;

    /**
     * Polygone de controle
     */
    QVector<Segment*> m_control_polygon;

public:
    /**
     * Afficher le polygone de controle
     * @param value valeur
     */
    void showControlPolygon(bool value);

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
};


#endif //OURBEPARAMETRIQUE_H
