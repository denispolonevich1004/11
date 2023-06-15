#include "colorpickerpaletteinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"
#include <QColorDialog>

ColorpickerPaletteInstrument::ColorpickerPaletteInstrument(QObject *parent) :
    AbstractInstrument(parent){

}

ColorpickerPaletteInstrument::ColorpickerPaletteInstrument(AbstractInstrument *parent) :
    AbstractInstrument(parent){

}

void ColorpickerPaletteInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea){
    (void)imageArea;
    (void)event;
}

void ColorpickerPaletteInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea){
    (void)imageArea;
    (void)event;
}

void ColorpickerPaletteInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea){
    (void)imageArea;
    (void)event;
}


void ColorpickerPaletteInstrument::showColorPalletteInstrument(ImageArea &imageArea){
    imageArea.setIsPaint(true);
    DataSingleton *dataSingleton = DataSingleton::Instance();
    QList<QColor> colorStack = dataSingleton->getColorStack();
    for(int i = 0; i < colorStack.size(); i++){
        QColorDialog::setCustomColor(colorStack.size() - i -1,colorStack[i]);
    }
    QColor color = QColorDialog::getColor(
                dataSingleton->getPrimaryColor(),
                &imageArea, "Обрати колір",
                {
                    QColorDialog::ShowAlphaChannel,
                    QColorDialog::DontUseNativeDialog
                });
    dataSingleton->pushColorStack(color);
    dataSingleton->setPrimaryColor(color);
    imageArea.emitPrimaryColorView();
    imageArea.setIsPaint(false);
    imageArea.emitRestorePreviousInstrument();
}


void ColorpickerPaletteInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool){
    (void)imageArea;
    (void)isSecondaryColor;
}
