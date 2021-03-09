#include "discretisation.h"

Discretisation::Discretisation(const QVector<Point*> &points) {
    object_points = points;
}

QVector<Point*> Discretisation::generateStepPoints(float step, QColor *color) const {
    QVector<Point*> points;
    for (float i = 0; i < 1.0f + step; i += step)
        points.push_back(getValue(i, *color));
    return points;
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
