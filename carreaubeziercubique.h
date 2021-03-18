#ifndef CARREAUBEZIERCUBIQUE_H
#define CARREAUBEZIERCUBIQUE_H

#include "courbebezier.h"
#include "polygon.h"

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
     * Points de controle
     */
    QVector<Point *> m_control_points;

    /**
     * Courbes de Bézier
     */
    QVector<CourbeBezier *> m_bezier_curves;

    /**
     * Segments de contrôle
     */
    QVector<Segment *> m_control_segments;

    /**
     * Couleur
     */
    QColor m_color = Qt::white;

public:
    /**
     * Constructeur
     * @param points liste des points de contrôle
     * @param color couleur
     * @param drawControlPolygon afficher le polygone de contrôle
     */
    explicit CarreauBezierCubique(const QVector<Point *> &points, const QColor &color = Qt::white,
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

    Point *getValue(float x, float y, const QColor &color = Qt::white) const override;

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
              const QVector<unsigned char> &drawTypes_override = {}) override;

    void render() override;
};

#endif //CARREAUBEZIERCUBIQUE_H
