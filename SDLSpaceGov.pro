TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cobject2d.cpp \
    cspaceship.cpp \
    cplanet.cpp \
    xenfains.cpp \
    cmeteor.cpp

LIBS += -lSDL2main
LIBS += -lGLU
LIBS += -lGL
LIBS += -lSDL2

HEADERS += \
    cobject2d.h \
    vars.h \
    cspaceship.h \
    cplanet.h \
    xenfains.h \
    cmeteor.h
