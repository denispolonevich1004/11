#include "curvelineinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPen>
#include <QPainter>
#include <QImage>
#include <QPainterPath>

CurveLineInstrument::CurveLineInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
    mPointsCount = 0;
}

void CurveLineInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        if(DataSingleton::Instance()->isResetCurve())
        {
            mPointsCount = 0;
            DataSingleton::Instance()->setResetCurve(false);
        }
        switch(mPointsCount)
        {
        //draw linear Bezier curve
        case 0:
            mImageCopy = *imageArea.getImage();
            mStartPoint = mEndPoint = mFirstControlPoint = mSecondControlPoint = event->pos();
            ++mPointsCount;
            break;
        //draw square Bezier curve
        case 1:
            mFirstControlPoint = mSecondControlPoint = event->pos();
            ++mPointsCount;
            break;
        //draw cubic Bezier curve
        case 2:
            mSecondControlPoint = event->pos();
            mPointsCount = 0;
            break;
        }
        imageArea.setIsPaint(true);
        makeUndoCommand(imageArea);
    }
}

void CurveLineInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        switch(mPointsCount)
        {
        //draw linear Bezier curve
        case 1:
            mEndPoint = event->pos();
            break;
        //draw square Bezier curve
        case 2:
            mFirstControlPoint = mSecondControlPoint = event->pos();
            break;
        //draw cubic Bezier curve
        case 0:
            mSecondControlPoint = event->pos();
            break;
        }

        imageArea.setImage(mImageCopy);
        if(event->buttons() & Qt::LeftButton)
            paint(imageArea, false);
        else if(event->buttons() & Qt::RightButton)
            paint(imageArea, true);
    }
}

void CurveLineInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        imageArea.setImage(mImageCopy);
        if(event->button() == Qt::LeftButton)
            paint(imageArea, false);
        else if(event->button() == Qt::RightButton)
            paint(imageArea, true);
        imageArea.setIsPaint(false);
    }
}

void CurveLineInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    QPainter painter(imageArea.getImage());
    painter.setRenderHint(QPainter::Antialiasing);
    //make Bezier curve path
    QPainterPath path;
    path.moveTo(mStartPoint);
    path.cubicTo(mFirstControlPoint, mSecondControlPoint, mEndPoint);
    //choose color
    painter.setPen(QPen(isSecondaryColor ? DataSingleton::Instance()->getSecondaryColor() :
                                           DataSingleton::Instance()->getPrimaryColor(),
                        DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //draw Bezier curve with given path
    painter.strokePath(path, painter.pen());

    imageArea.setEdited(true);
    painter.end();
    imageArea.update();
}

