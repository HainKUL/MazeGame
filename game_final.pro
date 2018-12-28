#-------------------------------------------------
#
# Project created by QtCreator 2018-12-05T11:27:42
#
#-------------------------------------------------

QT       += core gui \
            multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game_final
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

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    controller.cpp \
    enemyview.cpp \
    environmentview.cpp \
    healthpack.cpp \
    healthpackview.cpp \
    protagonistview.cpp \
    scene.cpp \
    model.cpp \
    textview.cpp \
    protagonisttextview.cpp \
    enemytextview.cpp \
    penemytextview.cpp \
    environmenttextview.cpp \
    healthpacktextview.cpp \
    environment.cpp \
    penemyview.cpp \
    pathfinder.cpp \
    xenemy.cpp \
    xenemyview.cpp \
    xenemytextview.cpp \
    tester.cpp \
    gameoverdialog.cpp

HEADERS += \
        mainwindow.h \
    controller.h \
    enemyview.h \
    environmentview.h \
    healthpack.h \
    healthpackview.h \
    protagonistview.h \
    scene.h \
    model.h \
    config.h \
    textview.h \
    protagonisttextview.h \
    enemytextview.h \
    penemytextview.h \
    environmenttextview.h \
    healthpacktextview.h \
    environment.h \
    penemyview.h \
    pathfinder.h \
    xenemy.h \
    xenemyview.h \
    xenemytextview.h \
    tester.h \
    gameoverdialog.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/world_v2/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/world_v2/debug/ -lworld
else:unix: LIBS += -L$$PWD/world_v2/ -lworld

INCLUDEPATH += $$PWD/world_v2
DEPENDPATH += $$PWD/world_v2

