#include "abstractinstrument.h"
#include "../imagearea.h"
#include "../undocommand.h"

AbstractInstrument::AbstractInstrument(QObject *parent) :
    QObject(parent)
{
}

void AbstractInstrument::makeUndoCommand(ImageArea &imageArea)
{
    imageArea.pushUndoCommand(new UndoCommand(imageArea.getImage(), imageArea));
}
