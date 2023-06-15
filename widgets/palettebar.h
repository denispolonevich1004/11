#ifndef PALETTEBAR_H
#define PALETTEBAR_H

#include "toolbar.h"
#include "palettebutton.h"

#include <QToolBar>

/**
  * @brief Toolbar with some number of differrent colors
  *
  */
class PaletteBar : public QToolBar
{
    Q_OBJECT

public:
    PaletteBar(ToolBar *toolBar);

private:
    /**
      * @brief Color buttons initializing
      *
      */
    void initializeItems();
    /**
     * @brief Create new QToolButton
     *
     * @param name Color name
     * @param color Color of button
     * @return QToolButton Created QToolButton.
     */

    PaletteButton *mColorButton;
    ToolBar *mToolBar;
    bool mIsRightButtonCLicked;

private slots:
    void colorClicked();

protected:
    void contextMenuEvent(QContextMenuEvent *);
};

#endif // PALETTEBAR_H
