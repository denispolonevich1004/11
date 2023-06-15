#include "negativeeffect.h"
#include "../imagearea.h"

NegativeEffect::NegativeEffect(QObject *parent) :
    AbstractEffect(parent)
{
}

void NegativeEffect::applyEffect(ImageArea &imageArea)
{
    imageArea.clearSelection();
    makeUndoCommand(imageArea);

    imageArea.getImage()->invertPixels(QImage::InvertRgb);
    imageArea.setEdited(true);
    imageArea.update();
}
