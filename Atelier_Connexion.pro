#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------
QT += serialport
QT       += core gui sql
QT += printsupport charts network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
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
    DuMesengerConnectionDialog.cpp \
    adherent.cpp \
    arduino.cpp \
    contrat.cpp \
    donneur.cpp \
    dossier_medical.cpp \
    historique.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    qrcodegen.cpp \
    ressourcehumaine.cpp \
    stmp.cpp \
    stock.cpp \
    tresorie.cpp \
    chat.cpp

HEADERS += \
    DuMesengerConnectionDialog.h \
    adherent.h \
    arduino.h \
    contrat.h \
    donneur.h \
    dossier_medical.h \
    historique.h \
        mainwindow.h \
    connection.h \
    qrcodegen.hpp \
    ressourcehumaine.h \
    stmp.h \
    stock.h \
    tresorie.h \
    chat.h

FORMS += \
    DuMesengerConnectionDialog.ui \
        mainwindow.ui \
chat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../../Downloads/Mon projet.jpg \
    Background (1).png \
    img/Background (1).png \
    img/Background (1).png \
    img/Mon projet.jpg

RESOURCES += \
    resource.qrc
