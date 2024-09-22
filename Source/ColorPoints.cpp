#include "ColorPoints.h"

ColorPoints::ColorPoints(QVector<ColorPoint> points)
{
    Q_ASSERT(points.size() >= 2);

    // Make sure all start points are valid
    {
        for(int i = 0; i < points.size(); ++i)
        {
            points[i].t = fmax(0.0f, fmin(points[i].t, 1.0f)); //0 <= t <= 1
        }

        float min = 1.0f;
        float max = 0.0f;
        int minIndex = 0;
        int maxIndex = 1;

        for(int i = 0; i < points.size(); ++i)
        {
            if(points[i].t <= min)
            {
                min = points[i].t;
                minIndex = i;
            }

            if(points[i].t >= max)
            {
                max = points[i].t;
                maxIndex = i;
            }
        }

        if(points[minIndex].t != 0.0f)
        {
            points[minIndex].t = 0.0f;
        }

        if(points[maxIndex].t != 1.0f)
        {
            points[maxIndex].t = 1.0f;
        }

    }

    QVector<ColorPoint> temp;

    // Make sure all start points are different
    {
        for(int i = 0; i < points.size(); ++i)
        {
            ColorPoint point = points[i];
            bool contains = false;
            for(int j = 0; j < temp.size(); ++j)
            {
                if(qFuzzyCompare(temp[j].t, point.t))
                {
                    contains = true;
                    break;
                }
            }

            if(!contains)
            {
                temp << point;
            }
        }
    }

    Q_ASSERT(temp.size() >= 2);

    QVector<ColorPoint> buffer;

    // Sort
    {
        while(temp.size() > 0)
        {
            float min = 1.0f;
            int index = 0;
            for(int i = 0; i < temp.size(); ++i)
            {
                if(temp[i].t <= min)
                {
                    min = temp[i].t;
                    index = i;
                }
            }

            buffer << temp.takeAt(index);
        }

    }

    this->colorPoints = buffer;
}

Color ColorPoints::colorAt(float t) const
{
    Q_ASSERT(0.0f <= t && t <= 1.0f);

    int index = 0;

    // In which interval does t belong?
    for(int i = 0; i < colorPoints.size() - 1; ++i)
    {
        if(colorPoints[i].t <= t && t <= colorPoints[i+1].t)
        {
            index = i;
            break;
        }
    }

    float t0 = colorPoints[index].t;
    float t1 = colorPoints[index + 1].t;
    float s = (t1 - t) / (t1 - t0);

    return colorPoints[index].color * s  + colorPoints[index + 1].color * (1 - s);
}

QString ColorPoints::toString()
{
    QString str;

    for(int i = 0; i < colorPoints.size(); i++)
    {
        str += colorPoints[i].toString();

        if(i < colorPoints.size() - 1)
        {
            str += ", ";
        }
    }

    return QString("{%1}").arg(str);
}
