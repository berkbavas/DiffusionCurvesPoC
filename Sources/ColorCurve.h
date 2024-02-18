#ifndef COLORCURVE_H
#define COLORCURVE_H

#include "Bezier.h"
#include "ColorPoints.h"
#include "Structs.h"

#include <QVector>

class ColorCurve {

public:
    ColorCurve(QVector<Point> controlPoints, ColorPoints leftColorPoints, ColorPoints rightColorPoints);
    Point valueAt(float t) const;
    Normal normalAt(float t, bool normalize = true) const;
    Tangent tangentAt(float t, bool normalize = true) const;
    float length(int intervals = 100) const;
    Color leftColorAt(float t) const;
    Color rightColorAt(float t) const;
    void scale(float factor);
    QString toString();

private:
    Bezier::Bezier curve;
    ColorPoints leftColorPoints;
    ColorPoints rightColorPoints;
};


#endif // COLORCURVE_H
