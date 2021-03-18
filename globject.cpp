#include "globject.h"

GLObject::~GLObject() {
    for (QOpenGLBuffer *verticesBuffer : m_verticesBuffers)
        verticesBuffer->destroy();
    for (QOpenGLBuffer *colorsBuffer : m_colorsBuffers)
        colorsBuffer->destroy();
    for (QOpenGLBuffer *normalsBuffer : m_normalsBuffers)
        normalsBuffer->destroy();
}

void GLObject::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *glFuncs,
                    const QVector<unsigned char> &drawTypes_override) {
    if (!m_rendered) render();

    for (int i = 0; i < m_verticesBuffers.count(); ++i) {
        m_verticesBuffers[i]->bind();
        program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3);
        program->enableAttributeArray("posAttr");

        m_colorsBuffers[i]->bind();
        program->setAttributeBuffer("colAttr", GL_FLOAT, 0, 3);
        program->enableAttributeArray("colAttr");

        m_normalsBuffers[i]->bind();
        program->setAttributeBuffer("norAttr", GL_FLOAT, 0, 3);
        program->enableAttributeArray("norAttr");

        unsigned char drawType = drawTypes_override.value(i) ? drawTypes_override[i] : m_drawTypes[i];

        glFuncs->glDrawArrays(drawType, 0, m_verticesBuffers[i]->size() / sizeof(GLfloat) / 3);

        program->disableAttributeArray("posAttr");
        m_verticesBuffers[i]->release();

        program->disableAttributeArray("colAttr");
        m_colorsBuffers[i]->release();

        program->disableAttributeArray("norAttr");
        m_normalsBuffers[i]->release();
    }
}

void GLObject::addVBO(const unsigned char &drawType) {
    auto *verticesBuffer = new QOpenGLBuffer();
    auto *colorsBuffer = new QOpenGLBuffer();
    auto *normalsBuffer = new QOpenGLBuffer();

    verticesBuffer->create();
    verticesBuffer->bind();
    verticesBuffer->allocate(m_vertices.constData(), 3 * m_vertices.count() * sizeof(GLfloat));
    verticesBuffer->release();

    QVector<QVector3D> colorsVector;
    for (const QColor &color : m_colors)
        colorsVector.append({(float) color.redF(), (float) color.greenF(), (float) color.blueF()});

    colorsBuffer->create();
    colorsBuffer->bind();
    colorsBuffer->allocate(colorsVector.constData(), 3 * colorsVector.count() * sizeof(GLfloat));
    colorsBuffer->release();

    normalsBuffer->create();
    normalsBuffer->bind();
    normalsBuffer->allocate(m_normals.constData(), 3 * m_normals.count() * sizeof(GLfloat));
    normalsBuffer->release();

    m_verticesBuffers.push_back(verticesBuffer);
    m_colorsBuffers.push_back(colorsBuffer);
    m_normalsBuffers.push_back(normalsBuffer);
    m_drawTypes.push_back(drawType);

    m_vertices.clear();
    m_colors.clear();
    m_normals.clear();
}

void GLObject::render() {
    m_rendered = true;
}

QVector3D GLObject::generateNormal(const QVector3D &p1, const QVector3D &p2, const QVector3D &p3) {
    QVector3D v12({p2.x() - p1.x(), p2.y() - p1.y(), p2.z() - p1.z()});
    QVector3D v13({p3.x() - p1.x(), p3.y() - p1.y(), p3.z() - p1.z()});
    return QVector3D::normal(v12, v13);
}