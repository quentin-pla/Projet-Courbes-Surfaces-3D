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
     * Destructeur
     */
    ~Polygon();

    /**
     * Afficher les extrémités du polygone
     * @param value valeur
     */
    void showExtremities(bool value);

    // GETTERS //

    /**
     * Obtenir les points du polygone
     * @return liste de points
     */
    const QVector<Point *> &getPoints() const;

    /**
     * Définir l'épaisseur des lignes
     * @param lineWidth
     */
    void setLineWidth(int lineWidth);

    /**
     * Activer la génération de normales en fonction de chaque point
     * @param value valeur
     */
    void enablePointsNormals(bool value);

    // OVERRIDE //

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
              const QVector<unsigned char> &drawTypes_override = {}) override;

    void render() override;
};


#endif //POLYGON_H
