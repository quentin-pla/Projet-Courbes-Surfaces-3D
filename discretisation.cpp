#include "discretisation.h"

Discretisation::Discretisation(const QVector<Point*> &points, QColor *color) {
    object_points = points;
    m_color = *color;
}

Point* Discretisation::getValue(float pos) const {
    auto start = object_points.first();
    auto end = object_points.last();

    float x = (1 - pos) * start->getX() + pos * end->getX();
    float y = (1 - pos) * start->getY() + pos * end->getY();
    float z = (1 - pos) * start->getZ() + pos * end->getZ();

    return new Point(x, y, z, new QColor(m_color));
}

QVector<Point*> Discretisation::generateStepPoints(float step) {
    m_points.clear();
    for (float i = step; i < 1.0f; i += step)
        m_points.push_back(getValue(i));
    return m_points;
}

float Discretisation::length() const {
    float res = 0.0f;
    for (int i = 0; i < object_points.count() - 1; ++i) {
        res += pow((object_points[i + 1])->getX() - (object_points[i])->getX(), 2.0f);
        res += pow((object_points[i + 1])->getY() - (object_points[i])->getY(), 2.0f);
        res += pow((object_points[i + 1])->getZ() - (object_points[i])->getZ(), 2.0f);
    }
    return sqrt(res);
}

const QVector<Point *> &Discretisation::getStepPoints() const {
    return m_points;
}
