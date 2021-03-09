#ifndef COURBEPARAMETRIQUE_H
#define COURBEPARAMETRIQUE_H

#include "discretisation.h"
#include "segment.h"

/**
 * Courbe paramétrique
 */
class CourbeParametrique : public GLObject, public Discretisation {
private:
    /**
     * Dessiner le polygone de controle
     */
    bool m_drawControlPolygon;

protected:
    /**
     * Constructeur
     * @param points liste des points de la courbe
     */
    explicit CourbeParametrique(const QVector<Point*> &points, QColor* color = new QColor(Qt::white),
                                const bool &drawControlPolygon = false);

    /**
     * Destructeur
     */
    ~CourbeParametrique() = default;

    /**
     * Liste des points de controle
     */
    QVector<Point*> m_control_points;

    /**
     * Polygone de controle
     */
    QVector<Segment*> m_control_polygon;

public:
    /**
     * Afficher le polygone de controle
     * @param value valeur
     */
    void showControlPolygon(bool value);

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) override;
};


#endif //OURBEPARAMETRIQUE_H
