#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

/**
 * Objet de scène OpenGL
 */
class GLObject {

public:
    /**
     * Dessiner l'objet
     * @param program programme OpenGL
     * @param glFuncs fonctions OpenGL
     */
    virtual void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs);

protected:
    /**
     * Constructeur
     */
    explicit GLObject() = default;

    /**
     * Destructeur
     */
    ~GLObject();

    /**
     * Liste des sommets
     */
    QVector<QVector3D> vertices;

    /**
     * Liste des couleurs
     */
    QVector<QColor> colors;

    /**
     * Liste des normales
     */
    QVector<QVector3D> normals;

    /**
     * Ajouter un VBO
     * @param drawType type de dessin
     */
    void addVBO(const unsigned char &drawType);

    /**
     * Est-ce que l'objet doit être rendu graphiquement
     */
    bool isRendered = false;

    /**
     * Générer les VBOs nécessaires pour l'affichage
     */
    virtual void render();

    /**
     * Générer la normale d'un carré / rectangle
     * @param p1 sommet 1
     * @param p2 sommet 2
     * @param p3 sommet 3
     * @param p4 sommet 4
     */
    void generateSquareNormal(const QVector3D &p1, const QVector3D &p2, const QVector3D &p3, const QVector3D &p4);

    /**
     * Générer la normale d'un triangle
     * @param p1 sommet 1
     * @param p2 sommet 2
     * @param p3 sommet 3
     */
    void generateTriangleNormal(const QVector3D &p1, const QVector3D &p2, const QVector3D &p3);

private:
    /**
     * Liste des tampons de sommets
     */
    QVector<QOpenGLBuffer*> verticesBuffers;

    /**
     * Liste des tampons de couleurs
     */
    QVector<QOpenGLBuffer*> colorsBuffers;

    /**
     * Liste des tampons de normales
     */
    QVector<QOpenGLBuffer*> normalsBuffers;

    /**
     * Type de dessin
     */
    QVector<unsigned char> drawTypes;
};

#endif //GLOBJECT_H
