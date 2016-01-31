TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    log.cpp \
    database.cpp \
    configs.cpp \
    app.cpp \
    server.cpp \
    tcpserver.cpp

HEADERS += \
    log.h \
    database.h \
    configs.h \
    app.h \
    server.h \
    tcpserver.h
