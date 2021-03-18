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

public:
    /**
     * Constructeur
     * @param points points
     * @param color couleur
     */
    explicit Polygon(const QVector<Point *> &points, const QColor &color = Qt::white);

    /**
     * Destructeur
     */
    ~Polygon() = default;

protected:

    // OVERRIDE //

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) override;

    void render() override;
};


#endif //POLYGON_H
