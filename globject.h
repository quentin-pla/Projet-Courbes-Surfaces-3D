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
     * Constructeur
     */
    explicit GLObject() = default;

    /**
     * Destructeur
     */
    ~GLObject();

    /**
     * Dessiner l'objet
     * @param program programme OpenGL
     * @param glFuncs fonctions OpenGL
     */
    virtual void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                      QMatrix4x4& world_mat, QMatrix4x4& proj_mat, QMatrix4x4& cam_mat, QMatrix4x4& shape_mat);

    /**
     * Appliquer des transformations
     */
    virtual void applyTransforms(QMatrix4x4&);

protected:
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
