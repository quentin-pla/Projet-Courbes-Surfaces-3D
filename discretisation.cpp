#include "discretisation.h"

Discretisation::Discretisation(const QVector<Point*> &points) {
    object_points = points;
}

QVector<Point *> Discretisation::generateStepPoints(float step, const QColor &color, bool extrem_points) const {
    QVector<Point *> points;
    float start = extrem_points ? 0 : step;
    float end = extrem_points ? 1.0f + step : 1.0f - step;
    for (float i = start; i < end; i += step) {
        if (i > 1.0f) i = 1.0f;
        points.push_back(getValue(i, color));
    }
    return points;
}

QVector<Point *>
Discretisation::generateXLinePoints(float x, float step, const QColor &color, bool extrem_points) const {
    QVector<Point *> points;
    float start = extrem_points ? 0 : step;
    float end = extrem_points ? 1.0f + step : 1.0f - step;
    for (float i = start; i < end; i += step) {
        if (i > 1.0f) i = 1.0f;
        points.push_back(getValue(x, i, color));
    }
    return points;
}

QVector<Point *>
Discretisation::generateYLinePoints(float y, float step, const QColor &color, bool extrem_points) const {
    QVector<Point *> points;
    float start = extrem_points ? 0 : step;
    float end = extrem_points ? 1.0f + step : 1.0f - step;
    for (float i = start; i < end; i += step) {
        if (i > 1.0f) i = 1.0f;
        points.push_back(getValue(i, y, color));
    }
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
