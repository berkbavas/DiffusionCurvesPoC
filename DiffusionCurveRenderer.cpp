#include "DiffusionCurveRenderer.h"
#include "Constants.h"
#include "Utils.h"

void DiffusionCurveRenderer::render(ColorCurve curve, Image *image)
{
    QVector<ColorCurve> curves(1, curve);
    render(curves, image);
}

void DiffusionCurveRenderer::render(QVector<ColorCurve> curves, Image *image)
{
    int bound = fmax(image->getWidth(), image->getHeight());
    ConstrainedImage *sample = new ConstrainedImage(bound * SCALE_FACTOR, bound * SCALE_FACTOR);

    for(int i = 0; i < curves.size(); i++)
    {
        curves[i].scale(SCALE_FACTOR);

        for (float t = 0; t <= 1.0; t += STEP)
        {
            Bezier::Point p = curves[i].valueAt(t);
            Bezier::Normal n = curves[i].normalAt(t);
            Color leftColor = curves[i].leftColorAt(t);
            Color rightColor = curves[i].rightColorAt(t);

            for (int j = -CURVE_THICKNESS; j <= CURVE_THICKNESS; j++)
            {
                Bezier::Point point = p + n * j;
                float s = (CURVE_THICKNESS + j) / (2.0f * CURVE_THICKNESS);
                Color color = leftColor * (1 - s) + rightColor * s;

                int x = round(point.x);
                int y = round(point.y);

                if(!sample->inBounds(y, x))
                    continue;

                sample->setColor(y, x, color);
                sample->setMask(y, x, true);
            }
        }
    }


#ifdef DEBUG
    sample->save(OUTPUT_DIR.absoluteFilePath("scaled.png"));
#endif

    while(sample->getSize() > bound * bound)
    {
        ConstrainedImage* temp = new ConstrainedImage(sample->getWidth() * 0.5f, sample->getHeight() * 0.5f);
        downsample(sample, temp);

        delete sample;
        sample = temp;
    }

#ifdef DEBUG
    sample->save(OUTPUT_DIR.absoluteFilePath("downsampled.png"));
#endif

    std::vector<ConstrainedImage*> samples;
    samples.push_back(sample);
    int index = 0;

    while(samples[index]->getWidth() > 1)
    {
        ConstrainedImage* image = new ConstrainedImage(samples[index]->getWidth() * 0.5f, samples[index]->getHeight() * 0.5f);
        downsample(samples[index++], image);
        samples.push_back(image);
    }

    index = samples.size() - 1;

    while(index > 0)
    {
        ConstrainedImage* down = samples[index];
        ConstrainedImage* up = samples[--index];
        upsample(down, up);
        smooth(up);
    }

    // Fill image
    for(int i = 0; i < image->getHeight(); i++)
        for(int j = 0; j < image->getWidth(); j++)
            image->setColor(i, j, samples[0]->getColor(i, j));


    // Clean up
    for(size_t i = 0; i < samples.size(); ++i)
        delete samples[i];

    samples.clear();
}

void DiffusionCurveRenderer::downsample(const ConstrainedImage *input, ConstrainedImage *output)
{
    for(int i = 0; i < output->getHeight(); ++i)
    {
        for(int j = 0; j < output->getWidth(); ++j)
        {
            int count = 0;
            Color outputColor(0,0,0);

            for(int r = 0; r < 2; ++r)
            {
                for(int c = 0; c < 2; ++c)
                {
                    int row = 2 * i + r;
                    int column = 2 * j + c;

                    if(input->getMask(row, column))
                    {
                        outputColor += input->getColor(row, column);
                        count++;
                    }

                }
            }

            if(count > 0)
            {
                output->setColor(i, j, outputColor / count);
                output->setMask(i, j, true);
            }
        }
    }
}

void DiffusionCurveRenderer::upsample(const ConstrainedImage *down, ConstrainedImage *up)
{
    for(int i = 0; i < down->getHeight(); ++i)
        for(int j = 0; j < down->getWidth(); ++j)
            for(int r = 0; r < 2; ++r)
                for(int c = 0; c < 2; ++c)
                {
                    int row = 2 * i + r;
                    int column = 2 * j + c;

                    if(!up->getMask(row, column))
                        up->setColor(row, column, down->getColor(i, j));
                }
}

void DiffusionCurveRenderer::smooth(ConstrainedImage *image)
{
    for(int pass = 0; pass < SMOOTH_ITERATIONS; ++pass)
        for(int i = 0; i < image->getSize(); ++i)
            if(!image->getMask(i))
                image->smooth(i, ConstrainedImage::ALL, ConstrainedImage::EXCLUSIVE);
}
