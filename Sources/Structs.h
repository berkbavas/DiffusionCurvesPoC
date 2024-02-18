#ifndef STRUCTS_H
#define STRUCTS_H

#include "Bezier.h"

#include <QString>

typedef Bezier::Vec2 Normal;
typedef Bezier::Vec2 Point;
typedef Bezier::Vec2 Tangent;

struct Color
{
    float r, g, b;
    Color() : r(0.0f), g(0.0f), b(0.0f) {}

    Color(float r, float g, float b) : r(r), g(g), b(b) {}

    Color operator+(const Color& other) const
    {
        return Color(r + other.r, g + other.g, b + other.b);
    }

    void operator+=(const Color& other)
    {
        r += other.r;
        g += other.g;
        b += other.b;
    }

    Color operator-(const Color& other) const
    {
        return Color(r - other.r, g - other.g, b - other.b);
    }

    void operator-=(const Color& other)
    {
        r -= other.r;
        g -= other.g;
        b -= other.b;
    }

    Color operator*(const float& f) const
    {
        return Color(f * r, f * g, f * b);
    }

    void operator*=(const float& f)
    {
        r *= f;
        g *= f;
        b *= f;
    }

    Color operator/(const float& f)
    {
        return Color(r / f,  g / f, b / f);
    }

    void operator/=(const float& f)
    {
        r /= f;
        g /= f;
        b /= f;
    }

    float length()
    {
        return sqrt(r*r + g*g + b*b);
    }

    static Color fromDecimal(uint8_t r, uint8_t g, uint8_t b)
    {
        return Color(r / 255.0f, g / 255.0f, b / 255.0f);
    }

    QString toString()
    {
        return QString("(%1, %2, %3)").arg(255 * r, 0, 'f', 0).arg(255 * g, 0, 'f', 0).arg(255 * b, 0, 'f', 0);
    }

};

struct ColorPoint {
    float t;
    Color color;
    ColorPoint(float t, Color color) : t(t), color(color) {}

    QString toString()
    {
        return QString("(%1, %2)").arg(t, 0, 'f', 2).arg(color.toString());
    }
};

#endif // STRUCTS_H
