#-------------------------------------------------
#
# Project created by QtCreator 2017-06-28T18:23:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageEncryptor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    imageencryptormodel.cpp \
    encryption/imageencryptor.cpp \
    encryption/evolutionencryptor.cpp \
    encryption/dnasequence.cpp \
    encryption/dna.cpp \
    encryption/dnaencryptor.cpp

HEADERS  += mainwindow.h \
    imageencryptormodel.h \
    imageencryptorpresenter.h \
    encryption/imageencryptor.h \
    encryption/evolutionencryptor.h \
    encryption/dnasequence.h \
    encryption/dna.h \
    encryption/dnaencryptor.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

unix|win32: LIBS += -L$$PWD/../build-ChaoticMaps-Desktop_Qt_5_9_1_MinGW_32bit-Release/release/ -lChaoticMaps

INCLUDEPATH += $$PWD/../ChaoticMaps
DEPENDPATH += $$PWD/../ChaoticMaps
