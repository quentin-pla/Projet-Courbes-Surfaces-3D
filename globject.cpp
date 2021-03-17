#include "globject.h"

GLObject::~GLObject() {
    for (QOpenGLBuffer *verticesBuffer : verticesBuffers)
        verticesBuffer->destroy();
    for (QOpenGLBuffer *colorsBuffer : colorsBuffers)
        colorsBuffer->destroy();
    for (QOpenGLBuffer *normalsBuffer : normalsBuffers)
        normalsBuffer->destroy();
}

void GLObject::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs) {
    if (!isRendered) render();

    for (int i = 0; i < verticesBuffers.count(); ++i) {
        verticesBuffers[i]->bind();
        program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3);
        program->enableAttributeArray("posAttr");

        colorsBuffers[i]->bind();
        program->setAttributeBuffer("colAttr", GL_FLOAT, 0, 3);
        program->enableAttributeArray("colAttr");

        normalsBuffers[i]->bind();
        program->setAttributeBuffer("norAttr", GL_FLOAT, 0, 3);
        program->enableAttributeArray("norAttr");

        glFuncs->glDrawArrays(drawTypes[i], 0, verticesBuffers[i]->size() / sizeof(GLfloat) / 3);

        program->disableAttributeArray("posAttr");
        verticesBuffers[i]->release();

        program->disableAttributeArray("colAttr");
        colorsBuffers[i]->release();

        program->disableAttributeArray("norAttr");
        normalsBuffers[i]->release();
    }
}

void GLObject::addVBO(const unsigned char &drawType) {
    auto *verticesBuffer = new QOpenGLBuffer();
    auto *colorsBuffer = new QOpenGLBuffer();
    auto *normalsBuffer = new QOpenGLBuffer();

    verticesBuffer->create();
    verticesBuffer->bind();
    verticesBuffer->allocate(vertices.constData(), 3 * vertices.count() * sizeof(GLfloat));
    verticesBuffer->release();

    QVector<QVector3D> colorsVector;
    for (const QColor& color : colors)
        colorsVector.append({(float) color.redF(), (float) color.greenF(), (float) color.blueF()});

    colorsBuffer->create();
    colorsBuffer->bind();
    colorsBuffer->allocate(colorsVector.constData(), 3 * colorsVector.count() * sizeof(GLfloat));
    colorsBuffer->release();

    normalsBuffer->create();
    normalsBuffer->bind();
    normalsBuffer->allocate(normals.constData(), 3 * normals.count() * sizeof(GLfloat));
    normalsBuffer->release();

    verticesBuffers.push_back(verticesBuffer);
    colorsBuffers.push_back(colorsBuffer);
    normalsBuffers.push_back(normalsBuffer);
    drawTypes.push_back(drawType);

    vertices.clear();
    colors.clear();
    normals.clear();
}

void GLObject::render() {
    isRendered = true;
}

void GLObject::generateSquareNormal(const QVector3D &p1, const QVector3D &p2, const QVector3D &p3, const QVector3D &p4) {
    generateTriangleNormal(p1, p2, p3);
    generateTriangleNormal(p3, p4, p1);
}

void GLObject::generateTriangleNormal(const QVector3D &p1, const QVector3D &p2, const QVector3D &p3) {
    QVector3D v12({p2.x() - p1.x(), p2.y() - p1.y(), p2.z() - p1.z()});
    QVector3D v13({p3.x() - p1.x(), p3.y() - p1.y(), p3.z() - p1.z()});
    normals.push_back(QVector3D::normal(v12, v13));
}

