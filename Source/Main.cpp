#include "DiffusionCurveRenderer.h"
#include "Image.h"
#include "Utils.h"
#include "Constants.h"

#include <QDebug>
#include <QDir>
#include <QVector>

int main() {

    qInfo() << "Working directory is" << QDir().absolutePath();

    if(!OUTPUT_DIR.exists())
    {
        qInfo() << "Output directory" << OUTPUT_DIR.absolutePath()<< "does not exist.";
        qInfo() << "Creating output directory...";

        if(!QDir().mkdir(OUTPUT_DIR_NAME))
        {
            qCritical() << "Could not create output directory.";
            qCritical() << "Exiting...";
            return -1;
        }

        qInfo() << "Output directory is created.";
    }

    // Simple test image
    {
        QVector<Point> controlPoints;
        controlPoints << Point(100, 500);
        controlPoints << Point(400, 100);
        controlPoints << Point(700, 500);

        QVector<ColorPoint> leftColors;
        leftColors << ColorPoint(0, Color::fromDecimal(0, 0, 255));
        leftColors << ColorPoint(1, Color::fromDecimal(255, 255, 0));

        QVector<ColorPoint> rightColors;
        rightColors << ColorPoint(0, Color::fromDecimal(0, 255, 0));
        rightColors << ColorPoint(1, Color::fromDecimal(255, 0, 255));

        ColorCurve curve(controlPoints, leftColors, rightColors);

        Image* image = new Image(800, 800);

        qInfo() << "Rendering test curve...";
        DiffusionCurveRenderer::render(curve, image);

        QString path = OUTPUT_DIR.absoluteFilePath("test.jpg");

        if(!image->save(path))
            qInfo() << "Could not save test curve.";
        else
            qInfo() << "Test curve is saved.";

        delete image;
    }


    if(!XML_DIR.exists())
    {
        qCritical() << "XML directory" << XML_DIR.absolutePath() << "does not exist.";
        qCritical() << "Exiting...";
        return -1;
    }

    QStringList files = XML_DIR.entryList(QStringList("*.xml"));

    for(int i = 0; i < files.size(); i++)
    {
        QString filename = files.at(i);
        QString path = XML_DIR.absoluteFilePath(filename);
        QVector<ColorCurve> curves;

        if(!Utils::readCurveData(path, curves))
            continue;

        for(int i = 0; i < curves.size(); i++)
            curves[i].scale(2);

        qInfo() << "Rendering" << filename;
        Image* image = new Image(1024, 1024);
        DiffusionCurveRenderer::render(curves, image);

        int index = filename.lastIndexOf(".");
        filename.remove(index, filename.length() - index).append(".jpg");
        path = OUTPUT_DIR.absoluteFilePath(filename);

        if(!image->save(path))
            qInfo() << "Could not save" << path;
        else
            qInfo() << filename << "is saved";

        delete image;
    }

    return 0;
}
