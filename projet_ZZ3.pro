TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = /home/user/workspace/include
LIBS = -L/usr/lib/x86_64-linux-gnu -lm -lpthread -lX11

SOURCES += \
    main.cpp \
    Ensemble.cpp \
    EnsembleDisplay.cpp \
    Exporter.cpp \
    Front.cpp \
    Graham.cpp \
    LoaderPoint.cpp \
    ParetoDisplay.cpp \
    Point.cpp \
    SquareGenerator.cpp \
    Traitement.cpp

HEADERS += \
    CImg.h \
    Ensemble.hpp \
    EnsembleDisplay.hpp \
    Exporter.hpp \
    Front.hpp \
    Graham.hpp \
    LoaderPoint.hpp \
    ParetoDisplay.hpp \
    Point.hpp \
    SquareGenerator.hpp \
    Traitement.hpp

