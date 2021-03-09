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
     * Obtenir la liste des points selon un pas spécifique
     * @param step pas
     * @return liste de points
     */
    QVector<Point*> generateStepPoints(float step, QColor* color = new QColor(Qt::white)) const;

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
