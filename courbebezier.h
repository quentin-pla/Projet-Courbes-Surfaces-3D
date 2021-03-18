#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H

#include "courbeparametrique.h"

/**
 * Courbe de Bézier
 */
class CourbeBezier : public CourbeParametrique {
public:
    /**
     * Constructeur
     * @param points points de controle
     * @param color couleur
     * @param drawControlPolygon afficher le polygone de controle
     */
    explicit CourbeBezier(const QVector<Point *> &points, QColor *color = new QColor(Qt::white),
                          const bool &drawControlPolygon = false);

    /**
     * Destructeur
     */
    ~CourbeBezier() = default;

    // OVERRIDE //

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) override;

    void render() override;

    Point *getValue(float pos, QColor *color = new QColor(Qt::white)) const override;
};


#endif //COURBEBEZIER_H
