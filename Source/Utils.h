#ifndef UTILS_H
#define UTILS_H

#include "ColorCurve.h"

#include <QDomDocument>
#include <QFile>
#include <QDebug>

class Utils {

private:
    Utils(){}

public:

    static bool readCurveData(QString path, QVector<ColorCurve> &curves)
    {
        QDomDocument document;

        // Read the file
        {
            QFile file(path);
            qInfo() << "Reading" << path;

            if (!file.open(QIODevice::ReadOnly))
            {
                qCritical() <<  "Could not load" << path;
                return false;
            }

            document.setContent(&file);
            file.close();
        }

        QDomElement root = document.documentElement();
        QDomElement component = root.firstChild().toElement();

        while(!component.isNull())
        {
            QVector<Point> controlPoints;
            QVector<ColorPoint> leftColorPoints;
            QVector<ColorPoint> rightColorPoints;

            if (component.tagName() == "curve")
            {
                QDomElement child = component.firstChild().toElement();

                while (!child.isNull())
                {
                    if(child.tagName() == "control_points_set")
                    {
                        QDomElement element = child.firstChild().toElement();

                        while(!element.isNull())
                        {
                            float x = element.attribute("y").toDouble();
                            float y = element.attribute("x").toDouble();

                            controlPoints << Point(x, y);
                            element = element.nextSibling().toElement();
                        }

                    }
                    else if(child.tagName() == "left_colors_set")
                    {
                        QDomElement element = child.firstChild().toElement();
                        int max = 0;

                        while(!element.isNull())
                        {
                            uint8_t r = element.attribute("B").toUInt();
                            uint8_t g = element.attribute("G").toUInt();
                            uint8_t b = element.attribute("R").toUInt();
                            int globalID = element.attribute("globalID").toInt();

                            leftColorPoints << ColorPoint(globalID, Color::fromDecimal(r, g, b));

                            if(globalID >= max)
                                max = globalID;

                            element = element.nextSibling().toElement();
                        }

                        for(int i = 0; i < leftColorPoints.size(); ++i)
                            leftColorPoints[i].t = leftColorPoints[i].t / max;

                    }
                    else if(child.tagName() == "right_colors_set")
                    {
                        QDomElement element = child.firstChild().toElement();
                        int max = 0;

                        while(!element.isNull())
                        {
                            uint8_t r = element.attribute("B").toUInt();
                            uint8_t g = element.attribute("G").toUInt();
                            uint8_t b = element.attribute("R").toUInt();
                            int globalID = element.attribute("globalID").toInt();

                            rightColorPoints << ColorPoint(globalID, Color::fromDecimal(r, g, b));

                            if(globalID >= max)
                                max = globalID;

                            element = element.nextSibling().toElement();
                        }

                        for(int i = 0; i < rightColorPoints.size(); ++i)
                            rightColorPoints[i].t = rightColorPoints[i].t / max;
                    }

                    child = child.nextSibling().toElement();
                }

            }

            if(controlPoints.size() >= 2)
                curves << ColorCurve(controlPoints, leftColorPoints, rightColorPoints);

            component = component.nextSibling().toElement();
        }

        return true;
    }

};

#endif // UTILS_H
