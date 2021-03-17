#ifndef CARREAUBEZIERCUBIQUE_H
#define CARREAUBEZIERCUBIQUE_H

#include "courbebezier.h"

/**
 * Carreau de Bézier cubique
 */
class CarreauBezierCubique : public GLObject, public Discretisation {
private:
    /**
     * Dessiner le polygone de controle
     */
    bool m_drawControlPolygon;

    /**
     * Liste des points de controle
     */
    QVector<Point *> m_control_points;

    /**
     * Liste des courbes de Bézier
     */
    QVector<CourbeBezier*> m_bezier_curves;

    /**
     * Polygone de controle
     */
    QVector<Segment*> m_control_polygon;

public:
    /**
     * Constructeur
     * @param points liste des points de contrôle
     * @param color couleur
     * @param drawControlPolygon afficher le polygone de contrôle
     */
    explicit CarreauBezierCubique(const QVector<Point *> &points, QColor *color = new QColor(Qt::white),
                                  const bool &drawControlPolygon = false);

    /**
     * Destructeur
     */
    ~CarreauBezierCubique() = default;

    /**
     * Afficher le polygone de controle
     * @param value valeur
     */
    void showControlPolygon(bool value);

    // OVERRIDE //

    Point* getValue(float x, float y, QColor* color = new QColor(Qt::white)) const override;

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) override;
};

#endif //CARREAUBEZIERCUBIQUE_H
