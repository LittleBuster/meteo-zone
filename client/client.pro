TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lboost_system -lpthread

SOURCES += main.cpp \
    app.cpp \
    log.cpp \
    tcpsocket.cpp \
    configs.cpp \
    sender.cpp

HEADERS += \
    app.h \
    log.h \
    tcpsocket.h \
    configs.h \
    sender.h
