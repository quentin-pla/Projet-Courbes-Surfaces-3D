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
     * Type de dessin
     */
    QVector<unsigned char> drawTypes;
};

#endif //GLOBJECT_H
