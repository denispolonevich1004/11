#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QMap>

#include "greenpaintenums.h"

QT_BEGIN_NAMESPACE
class QAction;
class QStatusBar;
class QTabWidget;
class ToolBar;
class PaletteBar;
class ImageArea;
class QLabel;
class QUndoGroup;
QT_END_NAMESPACE

/**
 * @brief Main window class.
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QStringList filePaths, QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void initializeMainMenu();
    void initializeStatusBar();
    void initializeToolBar();
    void initializePaletteBar();
    void initializeTabWidget();
    /**
     * @brief Initialize new tab for tab bar with new ImageArea and connect all needed slots.
     *
     * @param isOpen Flag which shows opens a new image or from file.
     * @param filePath File path
     */
    void initializeNewTab(const bool &isOpen = false, const QString &filePath = "");
    /**
     * @brief Get current ImageArea from current tab.
     *
     * @return ImageArea Geted ImageArea.
     */
    ImageArea* getCurrentImageArea();
    /**
     * @brief Get ImageArea from QTabWidget by index.
     *
     * @param index tab index
     * @return ImageArea, which corresponds to the index.
     */
    ImageArea* getImageAreaByIndex(int index);
    bool closeAllTabs();
    bool isSomethingModified();
    /**
     * @brief Update all shortcuts in menu bar.
     *
     */
    void updateShortcuts();

    QStatusBar *mStatusBar;
    QTabWidget *mTabWidget;
    ToolBar *mToolbar;
    PaletteBar *mPaletteBar;
    QLabel *mSizeLabel, *mPosLabel, *mColorPreviewLabel, *mColorRGBLabel;

    QMap<InstrumentsEnum, QAction*> mInstrumentsActMap;
    QMap<EffectsEnum, QAction*> mEffectsActMap;
    QAction *mSaveAction, *mSaveAsAction, *mCloseAction, *mPrintAction,
            *mUndoAction, *mRedoAction, *mCopyAction, *mCutAction,
            *mNewAction, *mOpenAction, *mExitAction, *mPasteAction, *mZoomInAction, *mZoomOutAction;
    QMenu *mInstrumentsMenu, *mEffectsMenu, *mToolsMenu;
    QUndoGroup *mUndoStackGroup;
    bool mPrevInstrumentSetted; /**< Used for magnifier */
private slots:
    void activateTab(const int &index);
    void setNewSizeToSizeLabel(const QSize &size);
    void setNewPosToPosLabel(const QPoint &pos);
    void setCurrentPipetteColor(const QColor &color);
    void clearStatusBarColor();
    void setInstrumentChecked(InstrumentsEnum instrument);
    void newAct();
    void openAct();
    void helpAct();
    void saveAct();
    void saveAsAct();
    void printAct();
    void copyAct();
    void pasteAct();
    void cutAct();
    void settingsAct();
    void effectsAct();
    void resizeImageAct();
    void resizeCanvasAct();
    void rotateLeftImageAct();
    void rotateRightImageAct();
    void zoomInAct();
    void zoomOutAct();
    void advancedZoomAct();
    void closeTabAct();
    void closeTab(int index);
    void setAllInstrumentsUnchecked(QAction *action);
    /**
     * @brief Instruments buttons handler.
     *
     * If some instrument has specific behavior, edit this slot.
     */
    void instumentsAct(bool state);
    void enableActions(int index);
    void enableCopyCutActions(bool enable);
    void clearImageSelection();
    void restorePreviousInstrument();
    void setInstrument(InstrumentsEnum instrument);
signals:
    void sendInstrumentChecked(InstrumentsEnum);

};

#endif // MAINWINDOW_H
