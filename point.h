#ifndef POINT_H
#define POINT_H

#include "globject.h"

class Point : public GLObject {
private:
    /**
     * Couleur
     */
    QColor m_color;

    /**
     * Taille du point
     */
    float m_size;

    /**
     * Coordonnées
     */
    QVector3D m_coords;

public:
    /**
     * Constructeur
     * @param color couleur
     * @param size taille
     */
    explicit Point(QColor* color = new QColor(Qt::white), float size = 20.0f);

    /**
     * Constructeur surchargé
     * @param x coordonnée X
     * @param y coordonnée Y
     * @param z coordonnée Z
     * @param color couleur
     * @param size taille du point
     */
    Point(float x, float y, float z, QColor* color = new QColor(Qt::white), float size = 20.0f);

    /**
     * Constructeur par copie
     */
    Point(const Point &);

    /**
     * Destructeur
     */
    ~Point() = default;

    /**
     * Dessiner le point
     * @param program programme
     * @param glFuncs fonctions OpenGL
     * @param world_mat matrice du monde
     * @param proj_mat matrice de projection
     * @param cam_mat matrice caméra
     * @param shape_mat matrice de transformation
     */
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
              QMatrix4x4& world_mat, QMatrix4x4& proj_mat, QMatrix4x4& cam_mat, QMatrix4x4& shape_mat) override;

    /**
     * Appliquer les transformations
     */
    void applyTransforms(QMatrix4x4&) override;

    // GETTERS & SETTERS //

    /**
     * Obtenir la taille
     * @return taille
     */
    float getSize() const;

    /**
     * Obtenir la couleur
     * @return couleur
     */
    QColor getColor() const;

    /**
     * Obtenir la coordonnée X
     * @return coordonnée X
     */
    float getX() const;

    /**
     * Obtenir la coordonnée Y
     * @return coordonnée Y
     */
    float getY() const;

    /**
     * Obtenir la coordonnée Z
     * @return coordonnée Z
     */
    float getZ() const;

    /**
     * Obtenir les coordonnées du point
     * @return coordonnées
     */
    QVector3D getCoords() const;

    /**
     * Définir la coordonnée X
     */
    void setX(const float &);

    /**
     * Définir la coordonnée Y
     */
    void setY(const float &);

    /**
     * Définir la coordonnée Z
     */
    void setZ(const float &);

    /**
     * Définir les coordonnées
     * @param newCoords nouvelles coordonnées
     */
    void setCoords(const QVector3D &newCoords);
};

#endif // POINT_H
