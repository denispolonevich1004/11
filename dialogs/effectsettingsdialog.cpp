#include <cmath>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "effectsettingsdialog.h"

EffectSettingsDialog::EffectSettingsDialog(const QImage &img, AbstractEffectSettings *settingsWidget, QWidget *parent) :
    QDialog(parent), mImage(img)
{
    mSettingsWidget = settingsWidget;
    mImagePreview = new ImagePreview(&mImage, this);
    mImagePreview->setMinimumSize(140, 140);

    mOkButton = new QPushButton(tr("Ок"), this);
    connect(mOkButton, SIGNAL(clicked()), this, SLOT(applyMatrix()));
    connect(mOkButton, SIGNAL(clicked()), this, SLOT(accept()));
    mCancelButton = new QPushButton(tr("Відмінити"), this);
    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    mApplyButton = new QPushButton(tr("Застосувати"), this);
    connect(mApplyButton, SIGNAL(clicked()), this, SLOT(applyMatrix()));
    connect(mApplyButton, SIGNAL(clicked()), mImagePreview, SLOT(update()));

    QHBoxLayout *hLayout_1 = new QHBoxLayout();

    hLayout_1->addWidget(mImagePreview);
    hLayout_1->addWidget(mSettingsWidget);

    QHBoxLayout *hLayout_2 = new QHBoxLayout();

    hLayout_2->addWidget(mOkButton);
    hLayout_2->addWidget(mCancelButton);
    hLayout_2->addWidget(mApplyButton);

    QVBoxLayout *vLayout = new QVBoxLayout();

    vLayout->addLayout(hLayout_1);
    vLayout->addLayout(hLayout_2);

    setLayout(vLayout);
}

QRgb EffectSettingsDialog::convolutePixel(const QImage &image, int x, int y, const QList<double> &kernelMatrix)
{
    int kernelSize = sqrt(kernelMatrix.size());

    double total = 0;
    double red = 0;
    double green = 0;
    double blue = 0;
    // TODO: some optimization can be made (maybe use OpenCV in future
    for(int r = -kernelSize / 2; r <= kernelSize / 2; ++r)
    {
        for(int c = -kernelSize / 2; c <= kernelSize / 2; ++c)
        {
            int kernelValue = kernelMatrix[(kernelSize / 2 + r) * kernelSize + (kernelSize / 2 + c)];
            total += kernelValue;
            red += qRed(image.pixel(x + c, y + r)) * kernelValue;
            green += qGreen(image.pixel(x + c, y + r)) * kernelValue;
            blue += qBlue(image.pixel(x + c, y + r)) * kernelValue;
        }
    }

    if(total == 0)
        return qRgb(qBound(0, qRound(red), 255), qBound(0, qRound(green), 255), qBound(0, qRound(blue), 255));

    return qRgb(qBound(0, qRound(red / total), 255), qBound(0, qRound(green / total), 255), qBound(0, qRound(blue / total), 255));
}

void EffectSettingsDialog::applyMatrix()
{
    QImage copy(mImage);

    for(int i = 2; i < copy.height() - 2; ++i)
    {
        for(int j = 2; j < copy.width() - 2; ++j)
        {
            copy.setPixel(j, i, convolutePixel(mImage, j, i, mSettingsWidget->getConvolutionMatrix()));
        }
    }

    mImage = copy;
}
