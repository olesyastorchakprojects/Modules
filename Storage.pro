QT += core sql widgets

CONFIG += c++11

TARGET = Storage
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Database/database.cpp \
    Database/Tables/projectstable.cpp \
    Objects/project.cpp

HEADERS += \
    Database/database.h \
    Database/Tables/projectstable.h \
    Objects/project.h
