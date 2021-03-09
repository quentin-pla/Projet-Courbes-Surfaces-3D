#include "globject.h"

GLObject::~GLObject() {
    for (QOpenGLBuffer *verticesBuffer : verticesBuffers)
        verticesBuffer->destroy();
    for (QOpenGLBuffer *colorsBuffer : colorsBuffers)
        colorsBuffer->destroy();
}

void GLObject::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                    QMatrix4x4& world_mat, QMatrix4x4& proj_mat, QMatrix4x4& cam_mat, QMatrix4x4& shape_mat) {
    shape_mat = world_mat;
    applyTransforms(shape_mat);

    program->setUniformValue("projMatrix", proj_mat);
    program->setUniformValue("mvMatrix", cam_mat * shape_mat);

    for (int i = 0; i < verticesBuffers.count(); ++i) {
        verticesBuffers[i]->bind();
        program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3);
        program->enableAttributeArray("posAttr");

        colorsBuffers[i]->bind();
        program->setAttributeBuffer("colAttr", GL_FLOAT, 0, 3);
        program->enableAttributeArray("colAttr");

        glFuncs->glDrawArrays(drawTypes[i], 0, verticesBuffers[i]->size());

        program->disableAttributeArray("posAttr");
        verticesBuffers[i]->release();

        program->disableAttributeArray("colAttr");
        colorsBuffers[i]->release();
    }
}

void GLObject::addVBO(const unsigned char &drawType) {
    auto *verticesBuffer = new QOpenGLBuffer();
    auto *colorsBuffer = new QOpenGLBuffer();

    verticesBuffer->create();
    verticesBuffer->bind();
    verticesBuffer->allocate(vertices.constData(), 3 * vertices.count() * sizeof(GLfloat));
    verticesBuffer->release();

    QVector<QVector3D> colorsVector;
    for (const QColor& color : colors)
        colorsVector.append(QVector3D(color.redF(), color.greenF(), color.blueF()));

    colorsBuffer->create();
    colorsBuffer->bind();
    colorsBuffer->allocate(colorsVector.constData(), 3 * colorsVector.count() * sizeof(GLfloat));
    colorsBuffer->release();

    verticesBuffers.push_back(verticesBuffer);
    colorsBuffers.push_back(colorsBuffer);
    drawTypes.push_back(drawType);

    vertices.clear();
    colors.clear();
}

void GLObject::applyTransforms(QMatrix4x4 &) {}