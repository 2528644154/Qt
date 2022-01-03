

greaterThan(QT_MAJOR_VERSION,4):QT+=widgets


QT       += core gui

TARGET = myMdi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mdichild.cpp

HEADERS  += mainwindow.h \
    mdichild.h

FORMS    += mainwindow.ui

RESOURCES += \
     myImage.qrc

RC_ICONS = myico4.ico
