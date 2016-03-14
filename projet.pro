#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T16:26:36
#
#-------------------------------------------------

QT += widgets
QT += xml

QT       += core

QT       -= gui

TARGET = projet
CONFIG   += console
CONFIG   -= app_bundle
CONFIG +=qt

TEMPLATE = app


SOURCES += main.cpp \
    agenda.cpp \
    timing.cpp \
    evenement.cpp \
    activite.cpp \
    tache.cpp \
    tacheunitaire.cpp \
    tachecomposite.cpp \
    projet.cpp \
    projetmanager.cpp \
    export.cpp \
    import.cpp \
    mainwindow.cpp \
    fenetreprojet.cpp \
    fenetresupmodprojet.cpp \
    fenetreunitaire.cpp \
    fenetrecomposite.cpp \
    activitemanager.cpp \
    fenetresave.cpp \
    fenetreload.cpp \
    fenetreprecedence.cpp \
    fenetreactivite.cpp \
    tachepreemptable.cpp \
    fenetresupmodactivite.cpp \
    vuesemaine.cpp \
    fenetresupmodtache.cpp \
    fenetreajoutprogrammation.cpp \
    fenetresupmodprogrammation.cpp \
    treeview.cpp

HEADERS += \
    agenda.h \
    timing.h \
    programmation.h \
    evenement.h \
    activite.h \
    tache.h \
    tacheunitaire.h \
    tachecomposite.h \
    projet.h \
    projetmanager.h \
    tachepreemptable.h \
    qt.h \
    export.h \
    import.h \
    mainwindow.h \
    fenetreprojet.h \
    fenetresupmodprojet.h \
    fenetreunitaire.h \
    fenetrecomposite.h \
    activitemanager.h \
    fenetresave.h \
    fenetreload.h \
    fenetreprecedence.h \
    fenetreactivite.h \
    fenetresupmodactivite.h \
    vuesemaine.h \
    fenetresupmodtache.h \
    fenetreajoutprogrammation.h \
    fenetresupmodprogrammation.h \
    treeview.h
