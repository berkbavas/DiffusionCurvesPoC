#include "Image.h"

#include <QDebug>

Image::Image() :
    width(0),
    height(0),
    data()
{

}

Image::Image(int width, int height) :
    width(width),
    height(height),
    data(width * height, Color(0.0f, 0.0f, 0.0f))
{

}

Image::Image(int width, int height, Color fillColor) :
    width(width),
    height(height),
    data(width * height, fillColor)
{

}

Image::~Image()
{

}

Color Image::operator[](int index) const
{
    return data[index];
}

Color& Image::operator[](int index)
{
    return data[index];
}

Color Image::getColor(int row, int column) const
{
    return data[width * row + column];
}

Color Image::getColor(int index) const
{
    return data[index];
}

void Image::setColor(int row, int column, const Color &color)
{
    data[width * row + column] = color;
}

void Image::setColor(int index, const Color &color)
{
    data[index] = color;
}

int Image::getWidth() const
{
    return width;
}

int Image::getHeight() const
{
    return height;
}

int Image::getSize() const
{
    return width * height;
}

bool Image::inBounds(int row, int column) const
{
    return 0 <= row && row < height && 0 <= column && column < width;
}

QImage Image::toQImage()
{
    QImage image(width, height, QImage::Format_RGB32);
    uchar* pixels = image.bits();

    for(int i = 0; i < getSize(); i++){
        pixels[4 * i + 2] = round(255 * data[i].r);
        pixels[4 * i + 1] = round(255 * data[i].g);
        pixels[4 * i + 0] = round(255 * data[i].b);
    }

    return image;
}

bool Image::save(QString filename)
{
    QImage image(width, height, QImage::Format_RGB32);
    uchar* pixels = image.bits();

    for(int i = 0; i < getSize(); i++){
        pixels[4 * i + 2] = round(255 * data[i].r);
        pixels[4 * i + 1] = round(255 * data[i].g);
        pixels[4 * i + 0] = round(255 * data[i].b);
    }

    return image.save(filename);
}
