#-------------------------------------------------
#
# Project created by QtCreator 2017-01-21T16:11:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ModeContingencyCalc
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
        maincontingencywindow.cpp \
    contingencydata.cpp \
    mattcalculations.cpp \
    reportoutput.cpp \
    saveandloadfunctions.cpp \
    unsavedchangesdialog.cpp \
    aboutdialog.cpp

HEADERS  += maincontingencywindow.h \
    constsants.h \
    contingencydata.h \
    mattcalculations.h \
    reportoutput.h \
    textforcontingencies.h \
    saveandloadfunctions.h \
    unsavedchangesdialog.h \
    aboutdialog.h

FORMS    += maincontingencywindow.ui \
    reportoutput.ui \
    unsavedchangesdialog.ui \
    aboutdialog.ui

DISTFILES += \
    calendar.ico \
    install.nsi \
    res.rc

RC_FILE = res.rc

#QMAKE_POST_LINK += windeployqt \"$$system_path($${OUT_PWD}/release/ModeContingencyCalc.exe)\" --dir \"$$system_path($${_PRO_FILE_PWD_}/Deploy)\"

#QMAKE_POST_LINK += && $$QMAKE_COPY \"$$system_path($${OUT_PWD}/release/ModeContingencyCalc.exe)\" \"$$system_path($${_PRO_FILE_PWD_}/Deploy/)\"
