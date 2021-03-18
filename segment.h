#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"
#include "discretisation.h"
#include <QVector>
#include <QColor>

/**
 * Segment
 */
class Segment : public GLObject, public Discretisation {
private:
    /**
     * Points du segment
     */
    QVector<Point *> m_points;

    /**
     * Couleur
     */
    QColor *m_color = new QColor(Qt::white);

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
    Segment(Point* start, Point* end, QColor* color = new QColor(Qt::white), const bool &drawExtremities = false);

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

    Point* getValue(float pos, QColor* color = new QColor(Qt::white)) const override;

    /**
     * Obtenir le point de départ
     * @return
     */
    Point* getStart() const;

    /**
     * Obtenir le point d'arrivée
     * @return
     */
    Point *getEnd() const;

    /**
     * Afficher les extrémités
     * @param value valeur
     */
    void showExtremities(bool value);

    // OVERRIDE //

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) override;

    void render() override;
};

#endif // SEGMENT_H
