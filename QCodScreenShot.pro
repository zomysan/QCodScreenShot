QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCodScreenShot
TEMPLATE = app
TRANSLATIONS = \
    translate/qcss_ja.ts

RC_ICONS = resource/icon.ico
ICON = resource/icon.ico

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/settingdialog.cpp \
    src/settings.cpp \
    src/screenshotsaver.cpp \
    src/screenshotdialog.cpp \
    src/imageconverter.cpp \
    src/countdownaction.cpp
HEADERS += \
    src/mainwindow.h \
    src/settingdialog.h \
    src/settings.h \
    src/screenshotsaver.h \
    src/screenshotdialog.h \
    src/imageconverter.h \
    src/countdownaction.h

FORMS += \
    src/mainwindow.ui \
    src/settingdialog.ui
