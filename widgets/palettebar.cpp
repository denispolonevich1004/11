#include "palettebar.h"
#include "../datasingleton.h"

PaletteBar::PaletteBar(ToolBar *toolbar) :
    QToolBar(tr("Colors"))
{
    mToolBar = toolbar;
    setMovable(false);
    initializeItems();
}

void PaletteBar::initializeItems()
{
    mColorButton = new PaletteButton(Qt::black);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::white);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::red);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkRed);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::green);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkGreen);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::blue);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkBlue);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::cyan);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkCyan);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::magenta);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkMagenta);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::yellow);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkYellow);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::gray);
    connect(mColorButton, &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    addWidget(mColorButton);
}

void PaletteBar::colorClicked()
{
    mToolBar->setPrimaryColorView();
    mToolBar->setSecondaryColorView();
}

void PaletteBar::contextMenuEvent(QContextMenuEvent *) { }
