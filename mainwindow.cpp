#include "mainwindow.h"
#include "widgets/toolbar.h"
#include "imagearea.h"
#include "datasingleton.h"
#include "dialogs/settingsdialog.h"
#include "widgets/palettebar.h"


#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QScrollArea>
#include <QLabel>
#include <QtEvents>
#include <QPainter>
#include <QInputDialog>
#include <QUndoGroup>
#include <QtCore/QTimer>
#include <QtCore/QMap>

MainWindow::MainWindow(QStringList filePaths, QWidget *parent)
    : QMainWindow(parent), mPrevInstrumentSetted(false)
{
    QSize winSize = DataSingleton::Instance()->getWindowSize();
    if (DataSingleton::Instance()->getIsRestoreWindowSize() &&  winSize.isValid()) {
        resize(winSize);
    }

    setWindowIcon(QIcon(":/media/logo/logo.png"));

    mUndoStackGroup = new QUndoGroup(this);

    initializeMainMenu();
    initializeToolBar();
    initializePaletteBar();
    initializeStatusBar();
    initializeTabWidget();

    if(filePaths.isEmpty())
    {
        initializeNewTab();
    }
    else
    {
        for(int i(0); i < filePaths.size(); i++)
        {
            initializeNewTab(true, filePaths.at(i));
        }
    }
    qRegisterMetaType<InstrumentsEnum>("InstrumentsEnum");
    DataSingleton::Instance()->setIsInitialized();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initializeTabWidget()
{
    mTabWidget = new QTabWidget();
    mTabWidget->setUsesScrollButtons(true);
    mTabWidget->setTabsClosable(true);
    mTabWidget->setMovable(true);
    connect(mTabWidget, &QTabWidget::currentChanged, this, &MainWindow::activateTab);
    connect(mTabWidget, &QTabWidget::currentChanged, this, &MainWindow::enableActions);
    connect(mTabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    setCentralWidget(mTabWidget);
}

void MainWindow::initializeNewTab(const bool &isOpen, const QString &filePath)
{
    ImageArea *imageArea;
    QString fileName(tr("Untitled"));
    if(isOpen && filePath.isEmpty())
    {
        imageArea = new ImageArea(isOpen, "", this);
        fileName = imageArea->getFileName();
    }
    else if(isOpen && !filePath.isEmpty())
    {
        imageArea = new ImageArea(isOpen, filePath, this);
        fileName = imageArea->getFileName();
    }
    else
    {
        imageArea = new ImageArea(false, "", this);
    }
    if (!imageArea->getFileName().isNull())
    {
        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setAttribute(Qt::WA_DeleteOnClose);
        scrollArea->setBackgroundRole(QPalette::Dark);
        scrollArea->setWidget(imageArea);

        mTabWidget->addTab(scrollArea, fileName);
        mTabWidget->setCurrentIndex(mTabWidget->count()-1);

        mUndoStackGroup->addStack(imageArea->getUndoStack());
        connect(imageArea, &ImageArea::sendPrimaryColorView, mToolbar, &ToolBar::setPrimaryColorView);
        connect(imageArea, &ImageArea::sendSecondaryColorView, mToolbar, &ToolBar::setSecondaryColorView);
        connect(imageArea, &ImageArea::sendRestorePreviousInstrument, this, &MainWindow::restorePreviousInstrument);
        connect(imageArea, &ImageArea::sendSetInstrument, this, &MainWindow::setInstrument);
        connect(imageArea, &ImageArea::sendNewImageSize, this, &MainWindow::setNewSizeToSizeLabel);
        connect(imageArea, &ImageArea::sendCursorPos, this, &MainWindow::setNewPosToPosLabel);
        connect(imageArea, &ImageArea::sendColor, this, &MainWindow::setCurrentPipetteColor);
        connect(imageArea, &ImageArea::sendEnableCopyCutActions, this, &MainWindow::enableCopyCutActions);
        connect(imageArea, &ImageArea::sendEnableSelectionInstrument, this, &MainWindow::instumentsAct);

        setWindowTitle(QString("%1 - GreenPainterApp").arg(fileName));
    }
    else
    {
        delete imageArea;
    }
}

void MainWindow::initializeMainMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Файл"));

    mNewAction = new QAction(tr("&Створити"), this);
    mNewAction->setIcon(QIcon::fromTheme("document-new", QIcon(":/media/actions-icons/document-new.png")));
    mNewAction->setIconVisibleInMenu(true);
    connect(mNewAction, &QAction::triggered, this, &MainWindow::newAct);
    fileMenu->addAction(mNewAction);

    mOpenAction = new QAction(tr("&Відкрити"), this);
    mOpenAction->setIcon(QIcon::fromTheme("document-open", QIcon(":/media/actions-icons/document-open.png")));
    mOpenAction->setIconVisibleInMenu(true);
    connect(mOpenAction, &QAction::triggered, this, &MainWindow::openAct);
    fileMenu->addAction(mOpenAction);

    mSaveAction = new QAction(tr("&Зберегти"), this);
    mSaveAction->setIcon(QIcon::fromTheme("document-save", QIcon(":/media/actions-icons/document-save.png")));
    mSaveAction->setIconVisibleInMenu(true);
    connect(mSaveAction, &QAction::triggered, this, &MainWindow::saveAct);
    fileMenu->addAction(mSaveAction);

    mSaveAsAction = new QAction(tr("Зберегти як"), this);
    mSaveAsAction->setIcon(QIcon::fromTheme("document-save-as", QIcon(":/media/actions-icons/document-save-as.png")));
    mSaveAsAction->setIconVisibleInMenu(true);
    connect(mSaveAsAction, &QAction::triggered, this, &MainWindow::saveAsAct);
    fileMenu->addAction(mSaveAsAction);

    mCloseAction = new QAction(tr("&Закрити"), this);
    mCloseAction->setIcon(QIcon::fromTheme("window-close", QIcon(":/media/actions-icons/window-close.png")));
    mCloseAction->setIconVisibleInMenu(true);
    connect(mCloseAction, &QAction::triggered, this, &MainWindow::closeTabAct);
    fileMenu->addAction(mCloseAction);

    fileMenu->addSeparator();

    mPrintAction = new QAction(tr("&Друкувати"), this);
    mPrintAction->setIcon(QIcon::fromTheme("document-print", QIcon(":/media/actions-icons/document-print.png")));
    mPrintAction->setIconVisibleInMenu(true);
    connect(mPrintAction, &QAction::triggered, this, &MainWindow::printAct);
    fileMenu->addAction(mPrintAction);

    fileMenu->addSeparator();

    mExitAction = new QAction(tr("&Вихід"), this);
    mExitAction->setIcon(QIcon::fromTheme("application-exit", QIcon(":/media/actions-icons/application-exit.png")));
    mExitAction->setIconVisibleInMenu(true);
    connect(mExitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(mExitAction);

    QMenu *editMenu = menuBar()->addMenu(tr("&Редагувати"));

    mUndoAction = mUndoStackGroup->createUndoAction(this, tr("&Скасувати дію"));
    mUndoAction->setIcon(QIcon::fromTheme("edit-undo", QIcon(":/media/actions-icons/edit-undo.png")));
    mUndoAction->setIconVisibleInMenu(true);
    mUndoAction->setEnabled(false);
    editMenu->addAction(mUndoAction);

    mRedoAction = mUndoStackGroup->createRedoAction(this, tr("&Повторити дію"));
    mRedoAction->setIcon(QIcon::fromTheme("edit-redo", QIcon(":/media/actions-icons/edit-redo.png")));
    mRedoAction->setIconVisibleInMenu(true);
    mRedoAction->setEnabled(false);
    editMenu->addAction(mRedoAction);

    editMenu->addSeparator();

    mCopyAction = new QAction(tr("&Копіювати"), this);
    mCopyAction->setIcon(QIcon::fromTheme("edit-copy", QIcon(":/media/actions-icons/edit-copy.png")));
    mCopyAction->setIconVisibleInMenu(true);
    mCopyAction->setEnabled(false);
    connect(mCopyAction, &QAction::triggered, this, &MainWindow::copyAct);
    editMenu->addAction(mCopyAction);

    mPasteAction = new QAction(tr("&Вставити"), this);
    mPasteAction->setIcon(QIcon::fromTheme("edit-paste", QIcon(":/media/actions-icons/edit-paste.png")));
    mPasteAction->setIconVisibleInMenu(true);
    connect(mPasteAction, &QAction::triggered, this, &MainWindow::pasteAct);
    editMenu->addAction(mPasteAction);

    mCutAction = new QAction(tr("&Вирізати"), this);
    mCutAction->setIcon(QIcon::fromTheme("edit-cut", QIcon(":/media/actions-icons/edit-cut.png")));
    mCutAction->setIconVisibleInMenu(true);
    mCutAction->setEnabled(false);
    connect(mCutAction, &QAction::triggered, this, &MainWindow::cutAct);
    editMenu->addAction(mCutAction);

    editMenu->addSeparator();

    QAction *settingsAction = new QAction(tr("&Налаштування"), this);
    settingsAction->setShortcut(QKeySequence::Preferences);
    settingsAction->setIcon(QIcon::fromTheme("document-properties", QIcon(":/media/actions-icons/document-properties.png")));
    settingsAction->setIconVisibleInMenu(true);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::settingsAct);
    editMenu->addAction(settingsAction);

    mInstrumentsMenu = menuBar()->addMenu(tr("&Інструменти"));

    QAction *mCursorAction = new QAction(tr("Виділення"), this);
    mCursorAction->setCheckable(true);
    mCursorAction->setIcon(QIcon::fromTheme("select-rectangular", QIcon(":/media/instruments-icons/cursor.png")));
    connect(mCursorAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mCursorAction);
    mInstrumentsActMap.insert(CURSOR, mCursorAction);

    QAction *mEraserAction = new QAction(tr("Гумка"), this);
    mEraserAction->setCheckable(true);
    mEraserAction->setIcon(QIcon::fromTheme("tool_eraser", QIcon(":/media/instruments-icons/lastic.png")));
    connect(mEraserAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mEraserAction);
    mInstrumentsActMap.insert(ERASER, mEraserAction);

    QAction *mColorPickerPaletteAction = new QAction(tr("Палітра вибору кольорів"), this);
    mColorPickerPaletteAction->setCheckable(true);
    mColorPickerPaletteAction->setIcon(QIcon::fromTheme("color-management", QIcon(":/media/instruments-icons/palette.png")));
    connect(mColorPickerPaletteAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mColorPickerPaletteAction);
    mInstrumentsActMap.insert(COLORPICKERPALETTE, mColorPickerPaletteAction);

    QAction *mMagnifierAction = new QAction(tr("Лупа"), this);
    mMagnifierAction->setCheckable(true);
    mMagnifierAction->setIcon(QIcon::fromTheme("zoom", QIcon(":/media/instruments-icons/loupe.png")));
    connect(mMagnifierAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mMagnifierAction);
    mInstrumentsActMap.insert(MAGNIFIER, mMagnifierAction);

    QAction *mPenAction = new QAction(tr("Перо"), this);
    mPenAction->setCheckable(true);
    mPenAction->setIcon(QIcon::fromTheme("tool_pen", QIcon(":/media/instruments-icons/pencil.png")));
    connect(mPenAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mPenAction);
    mInstrumentsActMap.insert(PEN, mPenAction);

    QAction *mLineAction = new QAction(tr("Лінія"), this);
    mLineAction->setCheckable(true);
    mLineAction->setIcon(QIcon::fromTheme("tool_line", QIcon(":/media/instruments-icons/line.png")));
    connect(mLineAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mLineAction);
    mInstrumentsActMap.insert(LINE, mLineAction);

    QAction *mSprayAction = new QAction(tr("Спрей"), this);
    mSprayAction->setCheckable(true);
    mSprayAction->setIcon(QIcon::fromTheme("tool_spraycan", QIcon(":/media/instruments-icons/spray.png")));
    connect(mSprayAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mSprayAction);
    mInstrumentsActMap.insert(SPRAY, mSprayAction);

    QAction *mFillAction = new QAction(tr("Заповнити"), this);
    mFillAction->setCheckable(true);
    mFillAction->setIcon(QIcon::fromTheme("color-fill", QIcon(":/media/instruments-icons/fill.png")));
    connect(mFillAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mFillAction);
    mInstrumentsActMap.insert(FILL, mFillAction);

    QAction *mRectangleAction = new QAction(tr("Прямокутник"), this);
    mRectangleAction->setCheckable(true);
    mRectangleAction->setIcon(QIcon::fromTheme("tool_rectangle", QIcon(":/media/instruments-icons/rectangle.png")));
    connect(mRectangleAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mRectangleAction);
    mInstrumentsActMap.insert(RECTANGLE, mRectangleAction);

    QAction *mEllipseAction = new QAction(tr("Еліпс"), this);
    mEllipseAction->setCheckable(true);
    mEllipseAction->setIcon(QIcon::fromTheme("tool_ellipse", QIcon(":/media/instruments-icons/ellipse.png")));
    connect(mEllipseAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mEllipseAction);
    mInstrumentsActMap.insert(ELLIPSE, mEllipseAction);

    QAction *curveLineAction = new QAction(tr("Крива"), this);
    curveLineAction->setCheckable(true);
    curveLineAction->setIcon(QIcon::fromTheme("tool_curve", QIcon(":/media/instruments-icons/curve.png")));
    connect(curveLineAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(curveLineAction);
    mInstrumentsActMap.insert(CURVELINE, curveLineAction);

    QAction *mTextAction = new QAction(tr("Текст"), this);
    mTextAction->setCheckable(true);
    mTextAction->setIcon(QIcon::fromTheme("tool-text", QIcon(":/media/instruments-icons/text.png")));
    connect(mTextAction, &QAction::triggered, this, &MainWindow::instumentsAct);
    mInstrumentsMenu->addAction(mTextAction);
    mInstrumentsActMap.insert(TEXT, mTextAction);

    // TODO: Add new instrument action here

    mEffectsMenu = menuBar()->addMenu(tr("&Ефекти"));

    QAction *grayEfAction = new QAction(tr("Чорно-білий"), this);
    connect(grayEfAction, &QAction::triggered, this, &MainWindow::effectsAct);
    mEffectsMenu->addAction(grayEfAction);
    mEffectsActMap.insert(GRAY, grayEfAction);

    QAction *negativeEfAction = new QAction(tr("Негатив"), this);
    connect(negativeEfAction, &QAction::triggered, this, &MainWindow::effectsAct);
    mEffectsMenu->addAction(negativeEfAction);
    mEffectsActMap.insert(NEGATIVE, negativeEfAction);

    QAction *binarizationEfAction = new QAction(tr("Бінаризація"), this);
    connect(binarizationEfAction, &QAction::triggered, this, &MainWindow::effectsAct);
    mEffectsMenu->addAction(binarizationEfAction);
    mEffectsActMap.insert(BINARIZATION, binarizationEfAction);

    QAction *gaussianBlurEfAction = new QAction(tr("Гаусовий фільтр"), this);
    connect(gaussianBlurEfAction, &QAction::triggered, this, &MainWindow::effectsAct);
    mEffectsMenu->addAction(gaussianBlurEfAction);
    mEffectsActMap.insert(GAUSSIANBLUR, gaussianBlurEfAction);

    QAction *gammaEfAction = new QAction(tr("Гамма"), this);
    connect(gammaEfAction, &QAction::triggered, this, &MainWindow::effectsAct);
    mEffectsMenu->addAction(gammaEfAction);
    mEffectsActMap.insert(GAMMA, gammaEfAction);

    QAction *sharpenEfAction = new QAction(tr("Різкість"), this);
    connect(sharpenEfAction, &QAction::triggered, this, &MainWindow::effectsAct);
    mEffectsMenu->addAction(sharpenEfAction);
    mEffectsActMap.insert(SHARPEN, sharpenEfAction);

    QAction *customEfAction = new QAction(tr("Власний"), this);
    connect(customEfAction, &QAction::triggered, this, &MainWindow::effectsAct);
    mEffectsMenu->addAction(customEfAction);
    mEffectsActMap.insert(CUSTOM, customEfAction);

    mToolsMenu = menuBar()->addMenu(tr("&Зображення"));

    QAction *resizeImAction = new QAction(tr("Розмір зображення"), this);
    connect(resizeImAction, &QAction::triggered, this, &MainWindow::resizeImageAct);
    mToolsMenu->addAction(resizeImAction);

    QAction *resizeCanAction = new QAction(tr("Розмір полотна"), this);
    connect(resizeCanAction, &QAction::triggered, this, &MainWindow::resizeCanvasAct);
    mToolsMenu->addAction(resizeCanAction);

    QMenu *rotateMenu = new QMenu(tr("Повернути"));

    QAction *rotateLAction = new QAction(tr("Проти годинникової стрілки"), this);
    rotateLAction->setIcon(QIcon::fromTheme("object-rotate-left", QIcon(":/media/actions-icons/object-rotate-left.png")));
    rotateLAction->setIconVisibleInMenu(true);
    connect(rotateLAction, &QAction::triggered, this, &MainWindow::rotateLeftImageAct);
    rotateMenu->addAction(rotateLAction);

    QAction *rotateRAction = new QAction(tr("За годинниковою стрілкою"), this);
    rotateRAction->setIcon(QIcon::fromTheme("object-rotate-right", QIcon(":/media/actions-icons/object-rotate-right.png")));
    rotateRAction->setIconVisibleInMenu(true);
    connect(rotateRAction, &QAction::triggered, this, &MainWindow::rotateRightImageAct);
    rotateMenu->addAction(rotateRAction);

    mToolsMenu->addMenu(rotateMenu);

    QMenu *zoomMenu = new QMenu(tr("Масштаб"));

    mZoomInAction = new QAction(tr("+"), this);
    mZoomInAction->setIcon(QIcon::fromTheme("zoom-in", QIcon(":/media/actions-icons/zoom-in.png")));
    mZoomInAction->setIconVisibleInMenu(true);
    connect(mZoomInAction, &QAction::triggered, this, &MainWindow::zoomInAct);
    zoomMenu->addAction(mZoomInAction);

    mZoomOutAction = new QAction(tr("-"), this);
    mZoomOutAction->setIcon(QIcon::fromTheme("zoom-out", QIcon(":/media/actions-icons/zoom-out.png")));
    mZoomOutAction->setIconVisibleInMenu(true);
    connect(mZoomOutAction, &QAction::triggered, this, &MainWindow::zoomOutAct);
    zoomMenu->addAction(mZoomOutAction);

    QAction *advancedZoomAction = new QAction(tr("Розширений масштаб"), this);
    advancedZoomAction->setIconVisibleInMenu(true);
    connect(advancedZoomAction, &QAction::triggered, this, &MainWindow::advancedZoomAct);
    zoomMenu->addAction(advancedZoomAction);

    mToolsMenu->addMenu(zoomMenu);

    QMenu *aboutMenu = menuBar()->addMenu(tr("&Інформація"));

    QAction *aboutAction = new QAction(tr("&Про GreenPainterApp"), this);
    aboutAction->setShortcut(QKeySequence::HelpContents);
    aboutAction->setIcon(QIcon::fromTheme("help-about", QIcon(":/media/actions-icons/help-about.png")));
    aboutAction->setIconVisibleInMenu(true);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::helpAct);
    aboutMenu->addAction(aboutAction);

    QAction *aboutQtAction = new QAction(tr("Про Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    aboutMenu->addAction(aboutQtAction);

    updateShortcuts();
}

void MainWindow::initializeStatusBar()
{
    mStatusBar = new QStatusBar();
    setStatusBar(mStatusBar);

    mSizeLabel = new QLabel();
    mPosLabel = new QLabel();
    mColorPreviewLabel = new QLabel();
    mColorRGBLabel = new QLabel();

    mStatusBar->addPermanentWidget(mSizeLabel, -1);
    mStatusBar->addPermanentWidget(mPosLabel, 1);
    mStatusBar->addPermanentWidget(mColorPreviewLabel);
    mStatusBar->addPermanentWidget(mColorRGBLabel, -1);
}

void MainWindow::initializeToolBar()
{
    mToolbar = new ToolBar(mInstrumentsActMap, this);
    addToolBar(Qt::LeftToolBarArea, mToolbar);
    connect(mToolbar, &ToolBar::sendClearStatusBarColor, this, &MainWindow::clearStatusBarColor);
    connect(mToolbar, &ToolBar::sendClearImageSelection, this, &MainWindow::clearImageSelection);
}

void MainWindow::initializePaletteBar()
{
    mPaletteBar = new PaletteBar(mToolbar);
    //addToolBar(Qt::BottomToolBarArea, mPaletteBar);
}

ImageArea* MainWindow::getCurrentImageArea()
{
    if (mTabWidget->currentWidget()) {
        QScrollArea *tempScrollArea = qobject_cast<QScrollArea*>(mTabWidget->currentWidget());
        ImageArea *tempArea = qobject_cast<ImageArea*>(tempScrollArea->widget());
        return tempArea;
    }
    return NULL;
}

ImageArea* MainWindow::getImageAreaByIndex(int index)
{
    QScrollArea *sa = static_cast<QScrollArea*>(mTabWidget->widget(index));
    ImageArea *ia = static_cast<ImageArea*>(sa->widget());
    return ia;
}

void MainWindow::activateTab(const int &index)
{
    if(index == -1)
        return;
    mTabWidget->setCurrentIndex(index);
    getCurrentImageArea()->clearSelection();
    QSize size = getCurrentImageArea()->getImage()->size();
    mSizeLabel->setText(QString("%1 x %2").arg(size.width()).arg(size.height()));

    if(!getCurrentImageArea()->getFileName().isEmpty())
    {
        setWindowTitle(QString("%1 - GreenPainterApp").arg(getCurrentImageArea()->getFileName()));
    }
    else
    {
        setWindowTitle(QString("%1 - GreenPainterApp").arg(tr("Untitled Image")));
    }
    mUndoStackGroup->setActiveStack(getCurrentImageArea()->getUndoStack());
}

void MainWindow::setNewSizeToSizeLabel(const QSize &size)
{
    mSizeLabel->setText(QString("%1 x %2").arg(size.width()).arg(size.height()));
}

void MainWindow::setNewPosToPosLabel(const QPoint &pos)
{
    mPosLabel->setText(QString("%1,%2").arg(pos.x()).arg(pos.y()));
}

void MainWindow::setCurrentPipetteColor(const QColor &color)
{
    mColorRGBLabel->setText(QString("RGB: %1,%2,%3").arg(color.red())
                         .arg(color.green()).arg(color.blue()));

    QPixmap statusColorPixmap = QPixmap(10, 10);
    QPainter statusColorPainter;
    statusColorPainter.begin(&statusColorPixmap);
    statusColorPainter.fillRect(0, 0, 15, 15, color);
    statusColorPainter.end();
    mColorPreviewLabel->setPixmap(statusColorPixmap);
}

void MainWindow::clearStatusBarColor()
{
    mColorPreviewLabel->clear();
    mColorRGBLabel->clear();
}

void MainWindow::newAct()
{
    initializeNewTab();
}

void MainWindow::openAct()
{
    initializeNewTab(true);
}

void MainWindow::saveAct()
{
    getCurrentImageArea()->save();
    mTabWidget->setTabText(mTabWidget->currentIndex(), getCurrentImageArea()->getFileName().isEmpty() ?
                               tr("Untitled Image") : getCurrentImageArea()->getFileName() );
}

void MainWindow::saveAsAct()
{
    getCurrentImageArea()->saveAs();
    mTabWidget->setTabText(mTabWidget->currentIndex(), getCurrentImageArea()->getFileName().isEmpty() ?
                               tr("Untitled Image") : getCurrentImageArea()->getFileName() );
}

void MainWindow::printAct()
{
    getCurrentImageArea()->print();
}

void MainWindow::settingsAct()
{
    SettingsDialog settingsDialog(this);
    if(settingsDialog.exec() == QDialog::Accepted)
    {
        settingsDialog.sendSettingsToSingleton();
        DataSingleton::Instance()->writeSettings();
        updateShortcuts();
    }
}

void MainWindow::copyAct()
{
    if (ImageArea *imageArea = getCurrentImageArea())
        imageArea->copyImage();
}

void MainWindow::pasteAct()
{
    if (ImageArea *imageArea = getCurrentImageArea())
        imageArea->pasteImage();
}

void MainWindow::cutAct()
{
    if (ImageArea *imageArea = getCurrentImageArea())
        imageArea->cutImage();
}

void MainWindow::updateShortcuts()
{
    mNewAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("New"));
    mOpenAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("Open"));
    mSaveAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("Save"));
    mSaveAsAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("SaveAs"));
    mCloseAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("Close"));
    mPrintAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey("Print"));
    mExitAction->setShortcut(DataSingleton::Instance()->getFileShortcutByKey(""
                                                                             ""
                                                                             ""
                                                                             ""
                                                                             ""
                                                                             ""));

    mUndoAction->setShortcut(DataSingleton::Instance()->getEditShortcutByKey("Undo"));
    mRedoAction->setShortcut(DataSingleton::Instance()->getEditShortcutByKey("Redo"));
    mCopyAction->setShortcut(DataSingleton::Instance()->getEditShortcutByKey("Copy"));
    mPasteAction->setShortcut(DataSingleton::Instance()->getEditShortcutByKey("Paste"));
    mCutAction->setShortcut(DataSingleton::Instance()->getEditShortcutByKey("Cut"));

    mInstrumentsActMap[CURSOR]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Cursor"));
    mInstrumentsActMap[ERASER]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Lastic"));
    mInstrumentsActMap[COLORPICKERPALETTE]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Pipette"));
    mInstrumentsActMap[MAGNIFIER]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Loupe"));
    mInstrumentsActMap[PEN]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Pen"));
    mInstrumentsActMap[LINE]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Line"));
    mInstrumentsActMap[SPRAY]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Spray"));
    mInstrumentsActMap[FILL]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Fill"));
    mInstrumentsActMap[RECTANGLE]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Rect"));
    mInstrumentsActMap[ELLIPSE]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Ellipse"));
    mInstrumentsActMap[CURVELINE]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Curve"));
    mInstrumentsActMap[TEXT]->setShortcut(DataSingleton::Instance()->getInstrumentShortcutByKey("Text"));
    // TODO: Add new instruments' shorcuts here

    mZoomInAction->setShortcut(DataSingleton::Instance()->getToolShortcutByKey("ZoomIn"));
    mZoomOutAction->setShortcut(DataSingleton::Instance()->getToolShortcutByKey("ZoomOut"));
}

void MainWindow::effectsAct()
{
    QAction *currentAction = static_cast<QAction*>(sender());
    getCurrentImageArea()->applyEffect(mEffectsActMap.key(currentAction));
}

void MainWindow::resizeImageAct()
{
    getCurrentImageArea()->resizeImage();
}

void MainWindow::resizeCanvasAct()
{
    getCurrentImageArea()->resizeCanvas();
}

void MainWindow::rotateLeftImageAct()
{
    getCurrentImageArea()->rotateImage(false);
}

void MainWindow::rotateRightImageAct()
{
    getCurrentImageArea()->rotateImage(true);
}

//todo : rotate degree input, or options

void MainWindow::zoomInAct()
{
    getCurrentImageArea()->zoomImage(1.0);
    getCurrentImageArea()->setZoomFactor(1.0);
}

void MainWindow::zoomOutAct()
{
    getCurrentImageArea()->zoomImage(1.0);
    getCurrentImageArea()->setZoomFactor(1.0);
}

void MainWindow::advancedZoomAct()
{
    bool ok;
    qreal factor = QInputDialog::getDouble(this, tr("Введіть коефіцієнт масштабування"), tr("Коефіцієнт масштабування:"), 2.5, 0, 1000, 5, &ok);
    if (ok)
    {
        getCurrentImageArea()->zoomImage(factor);
        getCurrentImageArea()->setZoomFactor(factor);
    }
}

void MainWindow::closeTabAct()
{
    closeTab(mTabWidget->currentIndex());
}

void MainWindow::closeTab(int index)
{
    ImageArea *ia = getImageAreaByIndex(index);
    if(ia->getEdited())
    {
        int ans = QMessageBox::warning(this, tr("Закриття вкладки"),
                                       tr("Файл змінено.\nВи хочете зберегти зміни?"),
                                       QMessageBox::Yes | QMessageBox::Default,
                                       QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape);
        switch(ans)
        {
        case QMessageBox::Yes:
            if (ia->save())
                break;
            return;
        case QMessageBox::Cancel:
            return;
        }
    }
    mUndoStackGroup->removeStack(ia->getUndoStack()); //for safety
    QWidget *wid = mTabWidget->widget(index);
    mTabWidget->removeTab(index);
    delete wid;
    if (mTabWidget->count() == 0)
    {
        setWindowTitle("Empty - GreenPainterApp");
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!isSomethingModified() || closeAllTabs())
    {
        DataSingleton::Instance()->setWindowSize(size());
        DataSingleton::Instance()->writeState();
        event->accept();
    }
    else
        event->ignore();
}

bool MainWindow::isSomethingModified()
{
    for(int i = 0; i < mTabWidget->count(); ++i)
    {
        if(getImageAreaByIndex(i)->getEdited())
            return true;
    }
    return false;
}

bool MainWindow::closeAllTabs()
{

    while(mTabWidget->count() != 0)
    {
        ImageArea *ia = getImageAreaByIndex(0);
        if(ia->getEdited())
        {
            int ans = QMessageBox::warning(this, tr("Закриття вкладки"),
                                           tr("Файл змінено.\nВи хочете зберегти зміни?"),
                                           QMessageBox::Yes | QMessageBox::Default,
                                           QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape);
            switch(ans)
            {
            case QMessageBox::Yes:
                if (ia->save())
                    break;
                return false;
            case QMessageBox::Cancel:
                return false;
            }
        }
        QWidget *wid = mTabWidget->widget(0);
        mTabWidget->removeTab(0);
        delete wid;
    }
    return true;
}

void MainWindow::setAllInstrumentsUnchecked(QAction *action)
{
    clearImageSelection();
    foreach (QAction *temp, mInstrumentsActMap)
    {
        if(temp != action)
            temp->setChecked(false);
    }
}

void MainWindow::setInstrumentChecked(InstrumentsEnum instrument)
{
    setAllInstrumentsUnchecked(NULL);
    if(instrument == PEN || instrument == INSTRUMENTS_COUNT)
        return;
    mInstrumentsActMap[instrument]->setChecked(true);
}

void MainWindow::instumentsAct(bool state)
{
    QAction *currentAction = static_cast<QAction*>(sender());
    if(state)
    {
        if(currentAction == mInstrumentsActMap[COLORPICKERPALETTE] && !mPrevInstrumentSetted)
        {
            DataSingleton::Instance()->setPreviousInstrument(DataSingleton::Instance()->getInstrument());
            mPrevInstrumentSetted = true;
            getCurrentImageArea()->colorpickerPaletteClicked();
        }
        setAllInstrumentsUnchecked(currentAction);
        currentAction->setChecked(true);
        DataSingleton::Instance()->setInstrument(mInstrumentsActMap.key(currentAction));
        emit sendInstrumentChecked(mInstrumentsActMap.key(currentAction));
    }
    else
    {
        setAllInstrumentsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(PEN);
        emit sendInstrumentChecked(PEN);
        if(currentAction == mInstrumentsActMap[CURSOR])
            DataSingleton::Instance()->setPreviousInstrument(mInstrumentsActMap.key(currentAction));
    }
}

void MainWindow::enableActions(int index)
{
    //if index == -1 it means, that there is no tabs
    bool isEnable = index == -1 ? false : true;

    mToolsMenu->setEnabled(isEnable);
    mEffectsMenu->setEnabled(isEnable);
    mInstrumentsMenu->setEnabled(isEnable);
    mToolbar->setEnabled(isEnable);
    mPaletteBar->setEnabled(isEnable);

    mSaveAction->setEnabled(isEnable);
    mSaveAsAction->setEnabled(isEnable);
    mCloseAction->setEnabled(isEnable);
    mPrintAction->setEnabled(isEnable);

    if(!isEnable)
    {
        setAllInstrumentsUnchecked(NULL);
        DataSingleton::Instance()->setInstrument(PEN);
        emit sendInstrumentChecked(PEN);
    }
}

void MainWindow::enableCopyCutActions(bool enable)
{
    mCopyAction->setEnabled(enable);
    mCutAction->setEnabled(enable);
}

void MainWindow::clearImageSelection()
{
    if (getCurrentImageArea())
    {
        getCurrentImageArea()->clearSelection();
        DataSingleton::Instance()->setPreviousInstrument(PEN);
    }
}

void MainWindow::restorePreviousInstrument()
{
    setInstrumentChecked(DataSingleton::Instance()->getPreviousInstrument());
    DataSingleton::Instance()->setInstrument(DataSingleton::Instance()->getPreviousInstrument());
    emit sendInstrumentChecked(DataSingleton::Instance()->getPreviousInstrument());
    mPrevInstrumentSetted = false;
}

void MainWindow::setInstrument(InstrumentsEnum instrument)
{
    setInstrumentChecked(instrument);
    DataSingleton::Instance()->setInstrument(instrument);
    emit sendInstrumentChecked(instrument);
    mPrevInstrumentSetted = false;
}

void MainWindow::helpAct()
{
    QMessageBox::about(this, tr("Про редактор"),
                       QString("<b>GreenPainterApp</b> %1: %2 <br> <br> %3: "
                               "<a href=\"https://gitlab.com/2019-2023/ipz19-1/polonevych-denis/diploma/greenpainterapp\">https://gitlab.com/2019-2023/ipz19-1/polonevych-denis/diploma/greenpainterapp</a>"
                               "<br> <br>%4:<ul>"
                               "<a href=\"mailto:ipz191_pdv@student.ztu.edu.ua\">Denys Polonevych</a></li>")
                       .arg(tr("Версія")).arg("1.0").arg(tr("Репозиторій")).arg(tr("Автор")));
}
