#include "ColorCurve.h"

ColorCurve::ColorCurve(QVector<Point> controlPoints, ColorPoints leftColorPoints, ColorPoints rightColorPoints) :
    curve(std::vector<Point>(controlPoints.begin(), controlPoints.end())),
    leftColorPoints(leftColorPoints),
    rightColorPoints(rightColorPoints)
{
    Q_ASSERT(controlPoints.size() >= 2);
}

Point ColorCurve::valueAt(float t) const
{
    return curve.valueAt(t);
}

Normal ColorCurve::normalAt(float t, bool normalize) const
{
    return curve.normalAt(t, normalize);
}

Normal ColorCurve::tangentAt(float t, bool normalize) const
{
    return curve.tangentAt(t, normalize);
}

float ColorCurve::length(int intervals) const
{
    return curve.length(intervals);
}

Color ColorCurve::leftColorAt(float t) const
{
    return leftColorPoints.colorAt(t);
}

Color ColorCurve::rightColorAt(float t) const
{
    return rightColorPoints.colorAt(t);
}

void ColorCurve::scale(float factor)
{
    for(size_t i = 0; i < curve.size(); ++i){
        curve[i] = curve[i] * factor;
    }
}

QString ColorCurve::toString()
{
    QString str;

    for(size_t i = 0; i < curve.size(); i++)
    {
        str += QString("(%1, %2)").arg(curve[i].x, 0, 'f', 2).arg(curve[i].y, 0, 'f', 2);

        if(i < curve.size() - 1)
        {
            str += ", ";
        }
    }

    return QString("%1{%2}\n%3%4\n%5%6")
        .arg("Control Points: ", str)
        .arg("Left Colors:    ", leftColorPoints.toString())
        .arg("Right Colors:   ", rightColorPoints.toString());
}

