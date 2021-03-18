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
     * @param points liste des points de contrôle
     * @param color couleur
     * @param drawControlPolygon afficher le polygone de contrôle
     */
    explicit CourbeParametrique(const QVector<Point *> &points, const QColor &color = Qt::white,
                                const bool &drawControlPolygon = false);

    /**
     * Destructeur
     */
    ~CourbeParametrique() = default;

    /**
     * Liste des points de controle
     */
    QVector<Point *> m_control_points;

    /**
     * Polygone de controle
     */
    QVector<Segment *> m_control_polygon;

    /**
     * Couleur
     */
    QColor m_color = Qt::white;

public:
    /**
     * Afficher le polygone de controle
     * @param value valeur
     */
    void showControlPolygon(bool value);

    // OVERRDIDE //

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
              const QVector<unsigned char> &drawTypes_override = {}) override;

    void render() override;
};


#endif //OURBEPARAMETRIQUE_H
