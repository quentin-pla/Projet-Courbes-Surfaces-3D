QT	+= core gui
CONFIG	+= c++14

QMAKE_CFLAGS = -Wunused-parameter

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visuCourbe
TEMPLATE = app

LIBS += -GLUT

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    globject.cpp \
    main.cpp \
    mainwindow.cpp \
    discretisation.cpp \
    glarea.cpp \
    segment.cpp \
    point.cpp \
    courbeparametrique.cpp \
    courbebezier.cpp \
    carreaubeziercubique.cpp \
    polygon.cpp \

HEADERS += \
    globject.h \
    mainwindow.h \
    discretisation.h \
    glarea.h \
    segment.h \
    point.h \
    courbeparametrique.h \
    courbebezier.h \
    carreaubeziercubique.h \
    polygon.h \

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc
