#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

#include <QWidget>

class ImagePreview : public QWidget
{
    Q_OBJECT
public:
    explicit ImagePreview(QImage *image, QWidget *parent);
    
signals:
    
public slots:
    
protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QImage *mImage;
};

#endif // IMAGEPREVIEW_H
