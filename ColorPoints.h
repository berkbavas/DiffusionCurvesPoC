#ifndef COLORPOINTS_H
#define COLORPOINTS_H

#include "Structs.h"

#include <QVector>

class ColorPoints
{
public:
    ColorPoints(QVector<ColorPoint> points);
    Color colorAt(float t) const;
    QString toString();

private:
    QVector<ColorPoint> colorPoints;

};

#endif // COLORPOINTS_H
