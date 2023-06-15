#ifndef BINARIZATIONEFFECT_H
#define BINARIZATIONEFFECT_H

#include "abstracteffect.h"

#include <QtCore/QObject>

/**
 * @brief Binarization effect class.
 *
 */
class BinarizationEffect : public AbstractEffect
{
    Q_OBJECT
public:
    explicit BinarizationEffect(QObject *parent = 0);
    
    void applyEffect(ImageArea &imageArea);

private:
    void makeBinarization(ImageArea &imageArea, int coeff1, int coeff2);
    
};

#endif // BINARIZATIONEFFECT_H
