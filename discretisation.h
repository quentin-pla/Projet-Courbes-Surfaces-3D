#ifndef DISCRETISATION_H
#define DISCRETISATION_H

#include "point.h"

class Discretisation {
public:
    /**
     * Constructeur
     * @param points liste des points
     * @param step pas
     * @param color couleur affichage
     */
    explicit Discretisation(const QVector<Point*> &points, QColor* color = new QColor(Qt::white));

    /**
     * Destructeur
     */
    ~Discretisation() = default;

    /**
     * Obtenir un point à une certaine position
     * @param pos position
     * @return point
     */
    virtual Point* getValue(float pos) const;

    /**
     * Obtenir la liste des points selon un pas spécifique
     * @param step pas
     * @return liste de points
     */
    QVector<Point*> generateStepPoints(float step);

    /**
     * Longueur totale
     * @return longueur
     */
    float length() const;

    /**
     * Obtenir les points générés
     * @return
     */
    const QVector<Point *> &getStepPoints() const;

private:
    /**
     * Liste des points de l'objet
     */
    QVector<Point*> object_points;

    /**
     * Couleur d'affichage
     */
    QColor m_color;

    /**
     * Points générés
     */
    QVector<Point*> m_points;
};


#endif //DISCRETISATION_H
