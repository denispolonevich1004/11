#ifndef SHARPENFILTERSETTINGS_H
#define SHARPENFILTERSETTINGS_H

#include <QSlider>

#include "abstracteffectsettings.h"

class SharpenFilterSettings : public AbstractEffectSettings
{
    Q_OBJECT
public:
    explicit SharpenFilterSettings(QWidget *parent = 0);
    
protected:
    virtual QList<double> getConvolutionMatrix();

private:
    QSlider *mIntensitySlider;
};

#endif // SHARPENFILTERSETTINGS_H
