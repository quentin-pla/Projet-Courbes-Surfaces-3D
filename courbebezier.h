#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H

#include "courbeparametrique.h"

class CourbeBezier : public CourbeParametrique {
public:
    /**
     * Constructeur
     * @param points points de controle
     * @param drawControlPolygon afficher le polygone de controle
     */
    explicit CourbeBezier(const QVector<Point*> &points, const bool &drawControlPolygon = false);

    /**
     * Destructeur
     */
    ~CourbeBezier() = default;

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) override;

    Point* getValue(float pos, const QColor &color) const override;
};


#endif //COURBEBEZIER_H
