#include "grayeffect.h"
#include "../imagearea.h"

GrayEffect::GrayEffect(QObject *parent) :
    AbstractEffect(parent)
{
}

void GrayEffect::applyEffect(ImageArea &imageArea)
{
    imageArea.clearSelection();
    makeUndoCommand(imageArea);

    for(int i(0); i < imageArea.getImage()->width(); i++)
    {
        for(int y(0); y < imageArea.getImage()->height(); y++)
        {
            QRgb pixel(imageArea.getImage()->pixel(i, y));
            int rgb = (int)(0.299 * qRed(pixel) + 0.587 * qGreen(pixel) + 0.114 * qBlue(pixel));
            pixel = qRgb(rgb, rgb, rgb);
            imageArea.getImage()->setPixel(i, y, pixel);
        }
    }
    imageArea.setEdited(true);
    imageArea.update();
}
