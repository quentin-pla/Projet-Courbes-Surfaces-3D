#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"

/**
 * Polygone
 */
class Polygon : public GLObject {
private:
    /**
     * Liste des points
     */
    QVector<Point *> m_points;

    /**
     * Couleur
     */
    QColor m_color;

    /**
     * Dessiner les extrémités
     */
    bool m_drawExtremities;

    /**
     * Épaisseur des lignes
     */
    int m_line_width;

    /**
     * Générer chaque normale en fonction des coordonnées d'un point
     */
    bool m_points_normals;

public:
    /**
     * Constructeur
     * @param points points
     * @param color couleur
     * @param drawExtremities afficher les points aux extrémités
     */
    explicit Polygon(const QVector<Point *> &points, const QColor &color = Qt::white, bool drawExtremities = false);

    /**
     * Afficher les extrémités du polygone
     * @param value valeur
     */
    void showExtremities(bool value);

    // GETTERS //

    const QVector<Point *> &getPoints() const;

    // SETTERS

    void setLineWidth(int lineWidth);

    void enablePointsNormals(bool value);

    // OVERRIDE //

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
              const QVector<unsigned char> &drawTypes_override = {}) override;

    void render() override;
};


#endif //POLYGON_H
