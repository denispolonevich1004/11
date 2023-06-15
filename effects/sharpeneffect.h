#ifndef SHARPENEFFECT_H
#define SHARPENEFFECT_H

#include "effectwithsettings.h"
#include "../widgets/sharpenfiltersettings.h"

#include <QtCore/QObject>

class SharpenEffect : public EffectWithSettings
{
    Q_OBJECT
public:
    explicit SharpenEffect(QObject *parent = 0) : EffectWithSettings(parent) {}

protected:
    // TODO: change type of widget
    virtual AbstractEffectSettings *getSettingsWidget() { return new SharpenFilterSettings(); }
};

#endif // SHARPENEFFECT_H
