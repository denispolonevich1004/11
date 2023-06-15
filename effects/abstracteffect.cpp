#include "abstracteffect.h"
#include "../undocommand.h"
#include "../imagearea.h"

AbstractEffect::AbstractEffect(QObject *parent) :
    QObject(parent)
{
}

void AbstractEffect::makeUndoCommand(ImageArea &imageArea)
{
    imageArea.pushUndoCommand(new UndoCommand(imageArea.getImage(), imageArea));
}
