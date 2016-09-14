TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    objectos2d.cpp \
    listaenc.cpp \
    ListaEnc.cpp \
    VectorMath.cpp \
    Elemento.cpp \
    clipping.cpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += gtk+-3.0

HEADERS += \
    objectos2d.h \
    Elemento.hpp \
    window.h \
    VectorMath.h \
    ListaEnc.h \
    Elemento.h \
    WindowFunctions.h \
    test_tarefa_02.h
