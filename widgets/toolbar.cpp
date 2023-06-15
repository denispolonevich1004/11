#include "toolbar.h"
#include "colorchooser.h"
#include "../datasingleton.h"

#include <QToolButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QAction>
#include <QtCore/QMap>

ToolBar::ToolBar(const QMap<InstrumentsEnum, QAction *> &actMap, QWidget *parent) :
    QToolBar(tr("Інструменти"), parent), mActMap(actMap)
{
    setMovable(false);
    initializeItems();
    mPrevInstrumentSetted = false;
}

QToolButton* ToolBar::createToolButton(QAction *act)
{
    QToolButton *toolButton = new QToolButton();
    toolButton->setMinimumSize(QSize(30, 30));
    toolButton->setMaximumSize(QSize(30, 30));
    toolButton->setDefaultAction(act);
    toolButton->setStatusTip(act->text());
    return toolButton;
}

void ToolBar::initializeItems()
{
    mCursorButton = createToolButton(mActMap[CURSOR]);
    mEraserButton = createToolButton(mActMap[ERASER]);
    mPenButton = createToolButton(mActMap[PEN]);
    mLineButton = createToolButton(mActMap[LINE]);
    mColorPickerPaletteButton = createToolButton(mActMap[COLORPICKERPALETTE]);
    mMagnifierButton = createToolButton(mActMap[MAGNIFIER]);
    mSprayButton = createToolButton(mActMap[SPRAY]);
    mFillButton = createToolButton(mActMap[FILL]);
    mRectangleButton = createToolButton(mActMap[RECTANGLE]);
    mEllipseButton = createToolButton(mActMap[ELLIPSE]);
    mCurveButton = createToolButton(mActMap[CURVELINE]);
    mTextButton = createToolButton(mActMap[TEXT]);

    QGridLayout *bLayout = new QGridLayout();
    bLayout->setMargin(3);
    bLayout->addWidget(mPenButton, 0, 0);
    bLayout->addWidget(mEraserButton, 0, 1);
    bLayout->addWidget(mColorPickerPaletteButton, 1, 0);
    bLayout->addWidget(mMagnifierButton, 1, 1);
    bLayout->addWidget(mCursorButton, 2, 0);
    bLayout->addWidget(mLineButton, 2, 1);
    bLayout->addWidget(mSprayButton, 3, 0);
    bLayout->addWidget(mFillButton, 3, 1);
    bLayout->addWidget(mRectangleButton, 4, 0);
    bLayout->addWidget(mEllipseButton, 4, 1);
    bLayout->addWidget(mCurveButton, 5, 0);
    bLayout->addWidget(mTextButton, 5, 1);

    QWidget *bWidget = new QWidget();
    bWidget->setLayout(bLayout);

    mPColorChooser = new ColorChooser(0, 0, 0, this);
    mPColorChooser->setStatusTip(tr("Основний колір"));
    mPColorChooser->setToolTip(tr("Основний колір"));
    connect(mPColorChooser, &ColorChooser::sendColor, this, &ToolBar::primaryColorChanged);

    mSColorChooser = new ColorChooser(255, 255, 255, this);
    mSColorChooser->setStatusTip(tr("Вторинний колір"));
    mSColorChooser->setToolTip(tr("Вторинний колір"));
    connect(mSColorChooser, &ColorChooser::sendColor, this, &ToolBar::secondaryColorChanged);

    QSpinBox *penSizeSpin = new QSpinBox();
    penSizeSpin->setRange(1, 20);
    penSizeSpin->setValue(1);
    penSizeSpin->setStatusTip(tr("Розмір ручки"));
    penSizeSpin->setToolTip(tr("Розмір ручки"));
    connect(penSizeSpin, SIGNAL(valueChanged(int)), this, SLOT(penValueChanged(int)));

    QGridLayout *tLayout = new QGridLayout();
    tLayout->setMargin(3);
    tLayout->addWidget(mPColorChooser, 0, 0);
    tLayout->addWidget(mSColorChooser, 0, 1);
    tLayout->addWidget(penSizeSpin, 1, 0, 1, 2);

    QWidget *tWidget = new QWidget();
    tWidget->setLayout(tLayout);

    addWidget(bWidget);
    addSeparator();
    addWidget(tWidget);
}

void ToolBar::penValueChanged(const int &value)
{
    DataSingleton::Instance()->setPenSize(value);
}

void ToolBar::primaryColorChanged(const QColor &color)
{
    DataSingleton::Instance()->setPrimaryColor(color);
}

void ToolBar::secondaryColorChanged(const QColor &color)
{
    DataSingleton::Instance()->setSecondaryColor(color);
}

void ToolBar::setPrimaryColorView()
{
    mPColorChooser->setColor(DataSingleton::Instance()->getPrimaryColor());
}

void ToolBar::setSecondaryColorView()
{
    mSColorChooser->setColor(DataSingleton::Instance()->getSecondaryColor());
}

void ToolBar::contextMenuEvent(QContextMenuEvent *)
{
}
