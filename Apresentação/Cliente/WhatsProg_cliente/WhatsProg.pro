#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T18:42:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhatsProg
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


SOURCES +=\
    dados_whatsprog.cpp \
    dados_cliente.cpp \
    logindialog.cpp \
    modelconversas.cpp \
    modelmensagens.cpp \
    whatsprogmain.cpp \
    main.cpp \
    winsocket.cpp \
    nova_msg.cpp

HEADERS  += \
    dados_whatsprog.h \
    dados_cliente.h \
    logindialog.h \
    modelconversas.h \
    modelmensagens.h \
    whatsprogmain.h \
    socket_whatsprog.h \
    dados_cliente.h \
    winsocket.h \
    nova_msg.h

FORMS    += \
    logindialog.ui \
    whatsprogmain.ui \
    nova_msg.ui

LIBS   += \
    -lWs2_32
