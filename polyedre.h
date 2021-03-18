#ifndef POLYEDRE_H
#define POLYEDRE_H

#include "point.h"

/**
 * Polyèdre
 */
class Polyedre : public GLObject {
private:
    /**
     * Liste des sommets
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
    Polyedre(const QVector<Point *> &points, const QColor &color = QColor(Qt::white));

    /**
     * Destructeur
     */
    ~Polyedre() = default;

protected:
    // OVERRIDE //

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) override;

    void render() override;
};


#endif //VISUCOURBE_POLYEDRE_H
