TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lboost_system -lpthread -lpq -llogger

SOURCES += main.cpp \
    database.cpp \
    configs.cpp \
    app.cpp \
    server.cpp \
    net/tcpserver.cpp \
    net/tcpclient.cpp

HEADERS += \
    database.h \
    configs.h \
    app.h \
    server.h \
    net/tcpserver.h \
    net/tcpclient.h
