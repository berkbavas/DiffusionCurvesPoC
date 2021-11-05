#ifndef IMAGE_H
#define IMAGE_H

#include <QVector>
#include <QImage>

#include "Structs.h"

class Image {

public:
    Image();
    Image(int width, int height);
    Image(int width, int height, Color fillColor);
    virtual ~Image();

    Color operator[](int index) const;
    Color &operator[](int index);

    Color getColor(int row, int column) const;
    Color getColor(int index) const;

    void setColor(int row, int column, const Color &color);
    void setColor(int index, const Color &color);

    int getWidth() const;
    int getHeight() const;
    int getSize() const;

    bool inBounds(int row, int column) const;

    QImage toQImage();
    bool save(QString fileName);

protected:
    int width, height;
    QVector<Color> data;

};

#endif // IMAGE_H
