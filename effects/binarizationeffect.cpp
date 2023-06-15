#include "binarizationeffect.h"
#include "../imagearea.h"

BinarizationEffect::BinarizationEffect(QObject *parent) :
    AbstractEffect(parent)
{
}

void BinarizationEffect::applyEffect(ImageArea &imageArea)
{
    makeUndoCommand(imageArea);

    // TODO: add dialog for setting parameters
    makeBinarization(imageArea, 200, 100);

    imageArea.setEdited(true);
    imageArea.update();
}

void BinarizationEffect::makeBinarization(ImageArea &imageArea, int coeff1, int coeff2)
{
    for (int x(0); x < imageArea.getImage()->width(); x++)
    {
        for (int y(0); y < imageArea.getImage()->height(); y++)
        {
            QRgb pixel = imageArea.getImage()->pixel(x, y);
            int r = (int)qRed(pixel);
            if (r >= coeff1)
                r = 0;
            else if (r >= coeff2 && r < coeff1)
                    r = 255;
            else
                r = 0;
            pixel = qRgb(r, r, r);
            imageArea.getImage()->setPixel(x, y, pixel);
        }
    }
}
