#ifndef DISCRETISATION_H
#define DISCRETISATION_H

#include "point.h"

/**
 * Discrétisation
 */
class Discretisation {
public:
    /**
     * Constructeur
     * @param points liste des points
     */
    explicit Discretisation(const QVector<Point*> &points);

    /**
     * Destructeur
     */
    ~Discretisation() = default;

    /**
     * Obtenir un point à une certaine position
     * @param pos position
     * @param color couleur
     * @return point
     */
    virtual Point* getValue(float pos, QColor* color) const { return nullptr; };

    /**
     * Obtenir un point à une certaine coordonnée
     * @param x coordonnée X
     * @param y coordonnée Y
     * @param color couleur
     * @return point
     */
    virtual Point* getValue(float x, float y, QColor* color) const { return nullptr; };

    /**
     * Obtenir la liste des points selon un pas spécifique
     * @param step pas
     * @param color couleur
     * @param extrem_points obtenir les points extrêmes
     * @return liste de points
     */
    QVector<Point*> generateStepPoints(float step, QColor* color = new QColor(Qt::white),
                                       bool extrem_points = true) const;

    /**
     * Obtenir la liste des points d'une ligne basée sur un axe X d'une surface
     * @param x coordonnée X
     * @param step pas
     * @param color couleur
     * @param extrem_points points extrêmes
     * @return liste de points
     */
    QVector<Point*> generateXLinePoints(float x, float step, QColor *color = new QColor(Qt::white),
                                        bool extrem_points = true) const;

    /**
     * Obtenir la liste des points d'une ligne basée sur un axe Y d'une surface
     * @param y coordonnée Y
     * @param step pas
     * @param color couleur
     * @param extrem_points points extrêmes
     * @return liste de points
     */
    QVector<Point*> generateYLinePoints(float y, float step, QColor *color = new QColor(Qt::white),
                                        bool extrem_points = true) const;

    /**
     * Longueur totale
     * @return longueur
     */
    float length() const;

private:
    /**
     * Liste des points de l'objet
     */
    QVector<Point*> object_points;
};


#endif //DISCRETISATION_H
