QT += core gui

CONFIG+= static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    include/model/copymanagement.h \
    include/model/direxception.h \
    src/view/mainwindow.h

SOURCES += \
    src/model/copymanagement.cpp \
    src/model/direxception.cpp \
    src/main.cpp \
    src/view/mainwindow.cpp

FORMS += \
    form/mainwindow.ui

RESOURCES += \
    res/res.qrc
