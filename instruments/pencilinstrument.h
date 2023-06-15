#ifndef PENCILINSTRUMENT_H
#define PENCILINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Pencil instrument class.
 *
 */
class PencilInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit PencilInstrument(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);
    
protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);
    
};

#endif // PENCILINSTRUMENT_H
