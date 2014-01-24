#-------------------------------------------------
#
# Project created by QtCreator 2013-09-20T18:35:34
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tetris
TEMPLATE = app

ICON=icon.ico

SOURCES += \
    keypad.cpp \
    figureprototype.cpp \
    figure.cpp \
    field.cpp \
    figurecassete.cpp \
    gameengine.cpp \
    gamewidget.cpp \
    pallete.cpp \
    main.cpp \
    advancedtimer.cpp \
    gamewindow.cpp \
    customgamedlg.cpp \
    about.cpp \
    gameproperties.cpp \
    record.cpp \
    recordtable.cpp \
    newrecorddlg.cpp \
    recordsdlg.cpp \
    centerof.cpp

HEADERS  += \
    keys.h \
    keypad.h \
    rotations.h \
    figuretype.h \
    figureprototype.h \
    figure.h \
    celltype.h \
    field.h \
    figurecassete.h \
    gameengine.h \
    gamewidget.h \
    pallete.h \
    advancedtimer.h \
    gamewindow.h \
    customgamedlg.h \
    about.h \
    version.h \
    gameproperties.h \
    record.h \
    recordtable.h \
    newrecorddlg.h \
    recordsdlg.h \
    centerof.h

FORMS    += \
    customgamedlg.ui \
    about.ui \
    newrecorddlg.ui \
    recordsdlg.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS += tetris_ru.ts
