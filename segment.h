#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"
#include "discretisation.h"

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
    QColor m_color;

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
    Segment(Point *start, Point *end, const QColor &color = Qt::white, const bool &drawExtremities = false);

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

    Point *getValue(float pos, const QColor &color = Qt::white) const override;

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

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
              const QVector<unsigned char> &drawTypes_override = {}) override;

    void render() override;
};

#endif // SEGMENT_H
