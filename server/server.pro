TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lboost_system -lpthread -lmysqlclient

SOURCES += main.cpp \
    log.cpp \
    database.cpp \
    configs.cpp \
    app.cpp \
    server.cpp \
    tcpserver.cpp \
    tcpclient.cpp

HEADERS += \
    log.h \
    database.h \
    configs.h \
    app.h \
    server.h \
    tcpserver.h \
    tcpclient.h
