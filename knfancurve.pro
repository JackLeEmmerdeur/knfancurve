#-------------------------------------------------
#
# Project created by QtCreator 2020-08-22T02:51:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts sql

TARGET = knfancurve
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    ChartWrapper.cpp \
    GPUHelpers.cpp \
    GPUStatsModel.cpp \
    IntRangeLineEdit.cpp \
    MainWindow.cpp \
    MiscHelpers.cpp \
    GPU.cpp \
    SMI.cpp \
    SettingsFrame.cpp \
    QutieHelpers.cpp \
    Main.cpp \
    CategoriesWidget.cpp \
    ChartsWidget.cpp \
    ChartRepainter.cpp

HEADERS += \
    ChartWrapper.h \
    GPUHelpers.h \
    GPUStatsModel.h \
    IntRangeLineEdit.h \
    MainWindow.h \
    MiscHelpers.h \
    GPU.h \
    SMI.h \
    SettingsFrame.h \
    QutieHelpers.h \
    CategoriesWidget.h \
    ChartsWidget.h \
    ChartRepainter.h

TRANSLATIONS = nfancurvytr_de.ts nfancurvytr_en.ts

# QMAKE_BUNDLE_DATA += nfancurvytr_de.qm

FORMS += \
    ChartWrapper.ui \
    ChartsWidget.ui \
    CategoriesWidget.ui \
    MainWindow.ui \
    SettingsFrame.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    app.qrc
