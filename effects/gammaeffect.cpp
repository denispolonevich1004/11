#include "gammaeffect.h"
#include "../imagearea.h"

#include <math.h>

GammaEffect::GammaEffect(QObject *parent) :
    AbstractEffect(parent)
{
}

void GammaEffect::applyEffect(ImageArea &imageArea)
{
    makeUndoCommand(imageArea);

    // TODO: add dialog for setting parameters
    makeGamma(imageArea, 2);

    imageArea.setEdited(true);
    imageArea.update();
}

void GammaEffect::makeGamma(ImageArea &imageArea, float modificator)
{
    for(int x(0); x < imageArea.getImage()->width(); x++)
    {
        for(int y(0); y < imageArea.getImage()->height(); y++)
        {
            QRgb pixel = imageArea.getImage()->pixel(x, y);
            float r = qRed(pixel);
            r = 255 * pow(r / 255, modificator);
            float g = qGreen(pixel);
            g = 255 * pow(g / 255, modificator);
            float b = qBlue(pixel);
            b = 255 * pow(b / 255, modificator);
            pixel = qRgb(r, g, b);
            imageArea.getImage()->setPixel(x, y, pixel);
        }
    }
}
