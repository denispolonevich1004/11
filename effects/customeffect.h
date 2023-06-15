#ifndef CUSTOMEFFECT_H
#define CUSTOMEFFECT_H

#include "effectwithsettings.h"
#include "../widgets/customfiltersettings.h"

class CustomEffect : public EffectWithSettings
{
    Q_OBJECT
public:
    explicit CustomEffect(QObject *parent = 0) : EffectWithSettings(parent) {}
    
protected:
    virtual AbstractEffectSettings* getSettingsWidget() { return new CustomFilterSettings(); }
};

#endif // CUSTOMEFFECT_H
