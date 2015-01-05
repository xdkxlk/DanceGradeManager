#-------------------------------------------------
#
# Project created by QtCreator 2014-10-02T18:22:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DanceGrades
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CExam.cpp \
    CJudges.cpp \
    CPeople.cpp \
    CProblem.cpp \
    readdialog.cpp \
    gradesdialog.cpp \
    finishdialog.cpp

HEADERS  += mainwindow.h \
    CExam.h \
    CJudges.h \
    CPeople.h \
    CProblem.h \
    SexEnum.h \
    readdialog.h \
    gradesdialog.h \
    finishdialog.h

FORMS    += mainwindow.ui \
    readdialog.ui \
    gradesdialog.ui \
    finishdialog.ui

RESOURCES += \
    DanceGrades.qrc
