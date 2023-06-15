#include <cmath>

#include "effectwithsettings.h"
#include "../imagearea.h"
#include "../dialogs/effectsettingsdialog.h"

EffectWithSettings::EffectWithSettings(QObject *parent) :
    AbstractEffect(parent)
{
}

void EffectWithSettings::applyEffect(ImageArea &imageArea)
{
    EffectSettingsDialog dlg(*imageArea.getImage(), getSettingsWidget());

    if(dlg.exec())
    {
        makeUndoCommand(imageArea);

        imageArea.setImage(dlg.getChangedImage());
        imageArea.setEdited(true);
        imageArea.update();
    }
}
