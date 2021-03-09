#ifndef SEGMENT_H
#define SEGMENT_H

#include "globject.h"
#include "point.h"
#include "discretisation.h"
#include <QVector>
#include <QColor>

class Segment : public GLObject, public Discretisation {
private:
    /**
     * Points du segment
     */
    QVector<Point*> m_points;

    /**
     * Dessiner les extrémités du segment
     */
    bool m_drawExtremities;

public:
    /**
     * Constructeur
     * @param start point de départ
     * @param end point d'arrivée
     * @param drawExtremities afficher les extrémités
     */
    Segment(Point* start, Point* end, const bool &drawExtremities = false);

    /**
     * Destructeur
     */
    ~Segment() = default;

    /**
     * Définir le point de départ
     */
    void setStart(Point*);

    /**
     * Définir le point d'arrivée
     */
    void setEnd(Point*);

    /**
     * Obtenir un point à une position spécifique
     * @param pos position
     * @return point
     */
    Point* getValue(float pos, const QColor &color) const override;

    /**
     * Obtenir le point de départ
     * @return
     */
    Point* getStart() const;

    /**
     * Obtenir le point d'arrivée
     * @return
     */
    Point* getEnd() const;

    /**
     * Afficher les extrémités
     * @param value valeur
     */
    void showExtremities(bool value);

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) override;
};

#endif // SEGMENT_H
