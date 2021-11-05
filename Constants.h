#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDir>
#include <QString>

const int SMOOTH_ITERATIONS = 100;
const int SCALE_FACTOR  = 4; // 2^x
const int CURVE_THICKNESS  = 2 * SCALE_FACTOR; // 2^x
const float STEP  = 0.0001f;

const QString XML_DIR_NAME = QString("XML");
const QDir XML_DIR = QDir(XML_DIR_NAME);

const QString OUTPUT_DIR_NAME = "Output";
const QDir OUTPUT_DIR = QDir(OUTPUT_DIR_NAME);


#endif // CONSTANTS_H
