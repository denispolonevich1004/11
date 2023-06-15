#ifndef CURVELINEINSTRUMENT_H
#define CURVELINEINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>
#include <QtCore/QPoint>

class CurveLineInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit CurveLineInstrument(QObject *parent = 0);
    
    virtual void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    virtual void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    virtual void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

private:
    QPoint mFirstControlPoint, mSecondControlPoint;
    unsigned int mPointsCount : 2; /**< Chaneges from 0 to 2, so 2 bits is enough. */
};

#endif // CURVELINEINSTRUMENT_H
