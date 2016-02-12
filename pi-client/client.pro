TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lboost_system -lpthread -lboost_thread -ldht22 -lwiringPi -lwiringPiDev

SOURCES += main.cpp \
    app.cpp \
    log.cpp \
    tcpsocket.cpp \
    configs.cpp \
    sender.cpp \
    lcd.cpp

HEADERS += \
    app.h \
    log.h \
    tcpsocket.h \
    configs.h \
    sender.h \
    lcd.h
