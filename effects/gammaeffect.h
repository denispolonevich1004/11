#ifndef GAMMAEFFECT_H
#define GAMMAEFFECT_H

#include "abstracteffect.h"

#include <QtCore/QObject>

/**
 * @brief Gray effect class.
 *
 */
class GammaEffect : public AbstractEffect
{
    Q_OBJECT
public:
    explicit GammaEffect(QObject *parent = 0);
    
    void applyEffect(ImageArea &imageArea);
    
private:
    void makeGamma(ImageArea &imageArea, float modificator);
};

#endif // GAMMAEFFECT_H
