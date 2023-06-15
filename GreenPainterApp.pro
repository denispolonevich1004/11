QT += printsupport
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additionaltools.cpp \
    datasingleton.cpp \
    dialogs/effectsettingsdialog.cpp \
    dialogs/resizedialog.cpp \
    dialogs/settingsdialog.cpp \
    dialogs/textdialog.cpp \
    effects/abstracteffect.cpp \
    effects/binarizationeffect.cpp \
    effects/effectwithsettings.cpp \
    effects/gammaeffect.cpp \
    effects/grayeffect.cpp \
    effects/negativeeffect.cpp \
    imagearea.cpp \
    instruments/abstractinstrument.cpp \
    instruments/abstractselection.cpp \
    instruments/colorpickerpaletteinstrument.cpp \
    instruments/curvelineinstrument.cpp \
    instruments/ellipseinstrument.cpp \
    instruments/eraserinstrument.cpp \
    instruments/fillinstrument.cpp \
    instruments/lineinstrument.cpp \
    instruments/magnifierinstrument.cpp \
    instruments/pencilinstrument.cpp \
    instruments/rectangleinstrument.cpp \
    instruments/selectioninstrument.cpp \
    instruments/sprayinstrument.cpp \
    instruments/textinstrument.cpp \
    main.cpp \
    mainwindow.cpp \
    qrc_resources.cpp \
    undocommand.cpp \
    widgets/colorchooser.cpp \
    widgets/customfiltersettings.cpp \
    widgets/gaussianblurfiltersettings.cpp \
    widgets/imagepreview.cpp \
    widgets/palettebar.cpp \
    widgets/palettebutton.cpp \
    widgets/sharpenfiltersettings.cpp \
    widgets/shortcutedit.cpp \
    widgets/toolbar.cpp

HEADERS += \
    additionaltools.h \
    datasingleton.h \
    dialogs/effectsettingsdialog.h \
    dialogs/resizedialog.h \
    dialogs/settingsdialog.h \
    dialogs/textdialog.h \
    effects/abstracteffect.h \
    effects/binarizationeffect.h \
    effects/customeffect.h \
    effects/effectwithsettings.h \
    effects/gammaeffect.h \
    effects/gaussianblureffect.h \
    effects/grayeffect.h \
    effects/negativeeffect.h \
    effects/sharpeneffect.h \
    greenpaintenums.h \
    imagearea.h \
    instruments/abstractinstrument.h \
    instruments/abstractselection.h \
    instruments/colorpickerpaletteinstrument.h \
    instruments/curvelineinstrument.h \
    instruments/ellipseinstrument.h \
    instruments/eraserinstrument.h \
    instruments/fillinstrument.h \
    instruments/lineinstrument.h \
    instruments/magnifierinstrument.h \
    instruments/pencilinstrument.h \
    instruments/rectangleinstrument.h \
    instruments/selectioninstrument.h \
    instruments/sprayinstrument.h \
    instruments/textinstrument.h \
    mainwindow.h \
    undocommand.h \
    widgets/abstracteffectsettings.h \
    widgets/colorchooser.h \
    widgets/customfiltersettings.h \
    widgets/gaussianblurfiltersettings.h \
    widgets/imagepreview.h \
    widgets/palettebar.h \
    widgets/palettebutton.h \
    widgets/sharpenfiltersettings.h \
    widgets/shortcutedit.h \
    widgets/toolbar.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \

DISTFILES += \
    media/actions-icons/application-exit.png \
    media/actions-icons/clear-gray.png \
    media/actions-icons/document-new.png \
    media/actions-icons/document-open.png \
    media/actions-icons/document-print.png \
    media/actions-icons/document-properties.png \
    media/actions-icons/document-save-as.png \
    media/actions-icons/document-save.png \
    media/actions-icons/edit-copy.png \
    media/actions-icons/edit-cut.png \
    media/actions-icons/edit-paste.png \
    media/actions-icons/edit-redo.png \
    media/actions-icons/edit-undo.png \
    media/actions-icons/help-about.png \
    media/actions-icons/object-rotate-left.png \
    media/actions-icons/object-rotate-right.png \
    media/actions-icons/window-close.png \
    media/actions-icons/zoom-in.png \
    media/actions-icons/zoom-out.png \
    media/instruments-icons/cursor.png \
    media/instruments-icons/cursor_fill.png \
    media/instruments-icons/cursor_loupe.png \
    media/instruments-icons/cursor_pipette.png \
    media/instruments-icons/cursor_spray.png \
    media/instruments-icons/curve.png \
    media/instruments-icons/ellipse.png \
    media/instruments-icons/fill.png \
    media/instruments-icons/lastic.png \
    media/instruments-icons/line.png \
    media/instruments-icons/loupe.png \
    media/instruments-icons/palette.png \
    media/instruments-icons/pencil.png \
    media/instruments-icons/pipette.png \
    media/instruments-icons/rectangle.png \
    media/instruments-icons/spray.png \
    media/instruments-icons/text.png \
    media/logo/logo.png \
    media/textures/transparent.jpg
