QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
RC_ICONS = ./res/image/icon/hi.ico

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += HAVE_CONFIG_H

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    globaldata.cpp \
    logfiles.cpp \
    loginwidget.cpp \
    main.cpp \
    basecontrol.cpp \
    mainwidget.cpp \
    mytools.cpp \
    person.cpp \
    personlist.cpp \
    socket.cpp \
    widgetmanage.cpp \
    Loading.cpp

HEADERS += \
    basecontrol.h \
    globaldata.h \
    logfiles.h \
    loginwidget.h \
    mainwidget.h \
    mytools.h \
    person.h \
    personlist.h \
    qrencode.h \
    socket.h \
    widgetmanage.h \
    Loading.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    loginwidget.ui \
    mainwidget.ui

RESOURCES += \
    QSS.qrc

LIBS += $$PWD/libqrencodeLib.a
