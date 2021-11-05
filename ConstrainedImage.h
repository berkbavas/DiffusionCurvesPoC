#ifndef CONSTRAINEDIMAGE_H
#define CONSTRAINEDIMAGE_H

#include "Image.h"

#include <QVector>

class ConstrainedImage : public Image
{

public:
    ConstrainedImage(int width, int height);
    ConstrainedImage(int width, int height, Color fillColor);

    enum SmoothingType
    {
        ALL = 0x00,
        ONLY_WITH_MASKS = 0x01
    };

    enum MeanType
    {
        EXCLUSIVE = 0x00,
        INCLUSIVE = 0x01
    };

    bool getMask(int index) const;
    bool getMask(int row, int column) const;
    void setMask(int index, bool mask);
    void setMask(int row, int column, bool mask);
    void resetMasks();
    void smooth(int index, SmoothingType smoothingType, MeanType meanType);

private:
    QVector<bool> masks;
};

#endif // CONSTRAINEDIMAGE_H
