#include "additionaltools.h"
#include "imagearea.h"
#include "dialogs/resizedialog.h"

#include <QImage>
#include <QPainter>
#include <QLabel>
#include <QTransform>
#include <QSize>
#include <QClipboard>
#include <QApplication>

AdditionalTools::AdditionalTools(ImageArea *pImageArea, QObject *parent) :
    QObject(parent){
    mPImageArea = pImageArea;
    //mPOriginalImageArea = new ImageArea(*pImageArea);
    mZoomedFactor = 1;
}

AdditionalTools::~AdditionalTools()
{

}

void AdditionalTools::resizeCanvas(int width, int height, bool flag)
{
    if(flag)
    {
        ResizeDialog resizeDialog(QSize(width, height), qobject_cast<QWidget *>(this->parent()));
        if(resizeDialog.exec() == QDialog::Accepted)
        {
            QSize newSize = resizeDialog.getNewSize();
            width = newSize.width();
            height = newSize.height();
        } else {
            return;
        }
    }

    if(width < 1 || height < 1)
        return;
    QImage *tempImage = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(tempImage);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(QRect(0, 0, width, height));
    painter.drawImage(0, 0, *mPImageArea->getImage());
    painter.end();

    mPImageArea->setImage(*tempImage);

    mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
                        mPImageArea->getImage()->rect().bottom() + 6);
    mPImageArea->setEdited(true);
    mPImageArea->clearSelection();
}

void AdditionalTools::resizeImage()
{
    ResizeDialog resizeDialog(mPImageArea->getImage()->size(), qobject_cast<QWidget *>(this->parent()));
    if(resizeDialog.exec() == QDialog::Accepted)
    {
        mPImageArea->setImage(mPImageArea->getImage()->scaled(resizeDialog.getNewSize()));
        mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
                            mPImageArea->getImage()->rect().bottom() + 6);
        mPImageArea->setEdited(true);
        mPImageArea->clearSelection();
    }
}

void AdditionalTools::rotateImage(bool flag)
{
    QTransform transform;
    if(flag)
    {
        transform.rotate(90);
    }
    else
    {
        transform.rotate(-90);
    }
    mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
    mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
                        mPImageArea->getImage()->rect().bottom() + 6);
    mPImageArea->update();
    mPImageArea->setEdited(true);
    mPImageArea->clearSelection();
}

bool AdditionalTools::zoomImage(qreal factor)
{
    mZoomedFactor *= factor;
    if(mZoomedFactor < 0.25)
    {
        mZoomedFactor = 0.25;
        return false;
    }
    else if(mZoomedFactor > 4)
    {
        mZoomedFactor = 4;
        return false;
    }
    else
    {
        QImage temImage = mPImageArea->getOriginalImage().transformed(QTransform::fromScale(factor, factor));
        mPImageArea->setImage(temImage);
        mPImageArea->resize((temImage.rect().width()),
                            (temImage.rect().height()));
        emit sendNewImageSize(temImage.size());
        mPImageArea->setEdited(true);
        mPImageArea->clearSelection();
        return true;
    }
}

bool AdditionalTools::rotateImage(int x, int y)
{
    QTransform transform = QTransform().rotate(x, Qt::Axis::XAxis).rotate(y, Qt::Axis::YAxis);
    mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
    mPImageArea->resize((mPImageArea->getImage()->rect().width()),
                        (mPImageArea->getImage()->rect().height()));
    mPImageArea->setEdited(true);
    mPImageArea->clearSelection();
    return true;
}
