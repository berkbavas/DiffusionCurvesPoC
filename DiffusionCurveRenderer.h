#ifndef DIFFUSIONCURVERENDERER_H
#define DIFFUSIONCURVERENDERER_H

#include "ColorCurve.h"
#include "ConstrainedImage.h"

class DiffusionCurveRenderer
{
private:
    DiffusionCurveRenderer(){}

public:
    static void render(ColorCurve curve, Image* image);
    static void render(QVector<ColorCurve> curves, Image* image);

private:
    static void downsample(const ConstrainedImage *input, ConstrainedImage *output);
    static void upsample(const ConstrainedImage *down, ConstrainedImage  *up);
    static void smooth(ConstrainedImage* image);
};

#endif // DIFFUSIONCURVERENDERER_H
