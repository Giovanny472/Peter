QT += gui
QT += widgets
QT += charts

CONFIG += c++11
CONFIG -= app_bundle

SOURCES += \
        PeterKey/coord/CNC2DPoint.cpp \
        PeterKeyPlot/PeterKeyPlot.cpp \
        main.cpp

HEADERS += \
    PeterKey/coord/CNC2DPoint.h \
    PeterKey/coord/CNC2DPointVector.h \
    PeterKeyPlot/PeterKeyPlot.h
