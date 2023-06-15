#include "colorchooser.h"

#include <QColor>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>

ColorChooser::ColorChooser(const int &r, const int &g, const int &b, QWidget *parent) :
    QLabel(parent)
{
    setFrameStyle(QFrame::Raised | QFrame::Box);
    mCurrentColor = new QColor(r, g, b);
    mPixmapColor = new QPixmap(20, 20);
    mPainterColor = new QPainter(mPixmapColor);
    mPainterColor->fillRect(0, 0, 20, 20, *mCurrentColor);
    mPainterColor->end();
    setMargin(3);
    setAlignment(Qt::AlignHCenter);
    setPixmap(*mPixmapColor);
}

ColorChooser::~ColorChooser()
{
    delete mCurrentColor;
    delete mPainterColor;
    delete mPixmapColor;
}

void ColorChooser::setColor(const QColor &color)
{
    *mCurrentColor = color;
    mPainterColor->begin(mPixmapColor);
    mPainterColor->fillRect(0, 0, 20, 20, *mCurrentColor);
    mPainterColor->end();
    setPixmap(*mPixmapColor);
}

void ColorChooser::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QColor color = QColorDialog::getColor(*mCurrentColor, this);
        if(color.isValid())
        {
            setColor(color);
            emit sendColor(color);
        }
    }
}
