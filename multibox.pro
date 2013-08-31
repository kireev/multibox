#-------------------------------------------------
#
# Project created by QtCreator 2013-03-10T12:38:45
#
#-------------------------------------------------

QT       += core gui network testlib
QT += network
CONFIG += STATIC

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multibox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    commonsource.cpp \
    config.cpp \
    filesystemsource.cpp \
    stringlistmodel.cpp \
    dropboxsource.cpp \
    cloudtablemodel.cpp \
    cloudtableview.cpp \
    startwindow.cpp \
    singletable.cpp \
    keypresseater.cpp \
    paintdelegate.cpp \
    mysortfilterproxymodel.cpp


HEADERS  += mainwindow.h \
    commonsource.h \
    config.h \
    filesystemsource.h \
    stringlistmodel.h \
    dropboxsource.h \
    cloudtablemodel.h \
    cloudtableview.h \
    startwindow.h \
    singletable.h \
    keypresseater.h \
    paintdelegate.h \
    mysortfilterproxymodel.h


FORMS    += \
    mainwindow.ui

#INCLUDEPATH += c:\Development\openSSl\include\
#LIBS += c:\Development\openSSl\

RESOURCES += \
    img.qrc

OTHER_FILES += \
    code_for_fututre.txt

INCLUDEPATH += /usr/include/
#INCLUDEPATH += /usr/include/c++
#INCLUDEPATH += /usr/include/c++/4.7

 QMAKE_CXXFLAGS += -std=c++0x
