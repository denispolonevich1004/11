#ifndef GAUSSIANBLUREFFECT_H
#define GAUSSIANBLUREFFECT_H

#include "effectwithsettings.h"
#include "../widgets/gaussianblurfiltersettings.h"

#include <QtCore/QObject>

/**
 * @brief Gaussian Blur effect class.
 *
 */
class GaussianBlurEffect : public EffectWithSettings
{
    Q_OBJECT
public:
    explicit GaussianBlurEffect(QObject *parent = 0) : EffectWithSettings(parent) {}
    
protected:
    // TODO: change type of widget
    virtual AbstractEffectSettings *getSettingsWidget() { return new GaussianBlurFilterSettings(); }
    
};

#endif // GAUSSIANBLUREFFECT_H
