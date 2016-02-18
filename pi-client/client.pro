TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lboost_system -lpthread -lboost_thread -ldht22 -lwiringPi -lwiringPiDev

SOURCES += main.cpp \
    app.cpp \
    log.cpp \
    configs.cpp \
    sender.cpp \
    lcd.cpp \
    tcpclient.cpp

HEADERS += \
    app.h \
    log.h \
    configs.h \
    sender.h \
    lcd.h \
    tcpclient.h
