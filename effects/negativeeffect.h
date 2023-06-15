#ifndef NEGATIVEEFFECT_H
#define NEGATIVEEFFECT_H

#include "abstracteffect.h"

#include <QtCore/QObject>

/**
 * @brief Negative effect class.
 *
 */
class NegativeEffect : public AbstractEffect
{
    Q_OBJECT

public:
    explicit NegativeEffect(QObject *parent = 0);

    void applyEffect(ImageArea &imageArea);

};

#endif // NEGATIVEEFFECT_H
