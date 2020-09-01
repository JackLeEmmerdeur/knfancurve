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
        main.cpp \
        mainwindow.cpp \
    categories.cpp \
    diaform.cpp \
    qutiehelpers.cpp \
    dia.cpp \
    settingsframe.cpp \
    mischelpers.cpp \
    nvidiagpu.cpp \
    nvidiasmi.cpp \
    gpuhelpers.cpp \
    gpustatsmodel.cpp \
    intrangelineedit.cpp

HEADERS += \
        mainwindow.h \
    categories.h \
    diaform.h \
    qutiehelpers.h \
    dia.h \
    settingsframe.h \
    mischelpers.h \
    nvidiagpu.h \
    nvidiasmi.h \
    gpuhelpers.h \
    gpustatsmodel.h \
    intrangelineedit.h

TRANSLATIONS = nfancurvytr_de.ts nfancurvytr_en.ts

# QMAKE_BUNDLE_DATA += nfancurvytr_de.qm

FORMS += \
        mainwindow.ui \
    categories.ui \
    diaform.ui \
    dia.ui \
    settingsframe.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    app.qrc
