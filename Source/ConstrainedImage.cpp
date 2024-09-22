#include "ConstrainedImage.h"

ConstrainedImage::ConstrainedImage(int width, int height) :
    Image(width, height),
    masks(width * height, false)
{

}

ConstrainedImage::ConstrainedImage(int width, int height, Color fillColor) :
    Image(width, height, fillColor),
    masks(width * height, false)
{

}

bool ConstrainedImage::getMask(int index) const
{
    return masks[index];
}

bool ConstrainedImage::getMask(int row, int column) const
{
    return masks[row * width + column];
}

void ConstrainedImage::setMask(int index, bool mask)
{
    masks[index] = mask;
}

void ConstrainedImage::setMask(int row, int column, bool mask)
{
    masks[row * width + column] = mask;
}

void ConstrainedImage::resetMasks()
{
    masks.fill(false);
}

void ConstrainedImage::smooth(int index, SmoothingType smoothingType, MeanType meanType)
{
    //     column
    //      [x]
    // [z]  [i]  [w]  row
    //      [y]

    int row = index / width;
    int column = index % height;
    int x = (row - 1) * width + column;
    int y = (row + 1) * width + column;
    int z = row * width + column - 1;
    int w = row * width + column + 1;

    Color color = meanType == INCLUSIVE ? data[index] : Color(0.0f, 0.0f, 0.0f);
    float count   = meanType == INCLUSIVE ? 1.0f : 0.0f;
    bool onlyWithMasks = smoothingType == ONLY_WITH_MASKS;

    if(0 < row)
    {
        if(onlyWithMasks)
        {
            if(masks[x])
            {
                color += data[x];
                count++;
            }
        }
        else
        {
            color += data[x];
            count++;
        }
    }

    if(row < height - 1)
    {
        if(onlyWithMasks)
        {
            if(masks[y])
            {
                color += data[y];
                count++;
            }
        }
        else
        {
            color += data[y];
            count++;
        }

    }

    if(column > 0)
    {
        if(onlyWithMasks)
        {
            if(masks[z])
            {
                color += data[z];
                count++;
            }
        }
        else
        {
            color += data[z];
            count++;
        }
    }

    if(column < height - 1)
    {
        if(onlyWithMasks)
        {
            if(masks[w])
            {
                color += data[w];
                count++;
            }
        }
        else
        {
            color += data[w];
            count++;
        }

    }

    if(count > 0)
    {
        color /= count;
        data[index] = color;
    }
}



