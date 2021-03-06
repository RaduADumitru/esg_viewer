QT       += core gui charts
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../utils/safeSQLexec.cpp \
    dbmanager/Initial_Population.cpp \
    dbmanager/dbmanager.cpp \
    generategraph.cpp \
    main.cpp \
    mainwindow.cpp \
    agency.cpp \
    company.cpp \
    rating.cpp \

HEADERS += \
    dbmanager/dbmanager.h \
    generategraph.h \
    mainwindow.h \
    agency.h \
    company.h \
    rating.h \
    types.h \

FORMS += \
    generategraph.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
