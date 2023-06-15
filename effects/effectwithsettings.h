#ifndef CONVOLUTIONMATRIXEFFECT_H
#define CONVOLUTIONMATRIXEFFECT_H

#include "abstracteffect.h"
#include "../widgets/abstracteffectsettings.h"

#include <QtCore/QObject>
#include <QRgb>
#include <QImage>

/**
 * @brief Base class for filters, which uses convolution matrix.
 *
 */
class EffectWithSettings : public AbstractEffect
{
    Q_OBJECT
public:
    explicit EffectWithSettings(QObject *parent = 0);

    virtual void applyEffect(ImageArea &imageArea);

protected:
    virtual AbstractEffectSettings* getSettingsWidget() = 0;

};

#endif // CONVOLUTIONMATRIXEFFECT_H
