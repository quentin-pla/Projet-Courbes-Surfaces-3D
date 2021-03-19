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
     * @param drawTypes_override types de dessin temporaire (pour chaque VBO)
     */
    virtual void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                      const QVector<unsigned char> &drawTypes_override = {});

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
    QVector<QVector3D> m_vertices;

    /**
     * Liste des couleurs
     */
    QVector<QColor> m_colors;

    /**
     * Liste des normales
     */
    QVector<QVector3D> m_normals;

    /**
     * Est-ce que l'objet doit être rendu graphiquement
     */
    bool m_rendered = false;

    /**
    * Ajouter un VBO
    * @param drawType type de dessin
    */
    void addVBO(const unsigned char &drawType);

    /**
     * Générer une normale
     * @param p1 sommet 1
     * @param p2 sommet 2
     * @param p3 sommet 3
     */
    QVector3D generateNormal(const QVector3D &p1, const QVector3D &p2, const QVector3D &p3);

    /**
     * Générer les VBOs nécessaires pour l'affichage
     */
    virtual void render();

private:
    /**
     * Liste des tampons de sommets
     */
    QVector<QOpenGLBuffer *> m_verticesBuffers;

    /**
     * Liste des tampons de couleurs
     */
    QVector<QOpenGLBuffer *> m_colorsBuffers;

    /**
     * Liste des tampons de normales
     */
    QVector<QOpenGLBuffer *> m_normalsBuffers;

    /**
     * Type de dessin pour chaque VBO
     */
    QVector<unsigned char> m_drawTypes;
};

#endif //GLOBJECT_H
