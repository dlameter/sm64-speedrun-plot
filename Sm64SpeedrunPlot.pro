QT += core gui widgets charts

CONFIG += qt warn_on debug

SOURCES += main.cpp data_helper.cpp run.cpp category.cpp level.cpp leveled_category.cpp game.cpp interactive_qchart.cpp
HEADERS += data_helper.h run.h category.h level.h leveled_category.h game.h interactive_qchart.h

TARGET = Sm64SpeedrunPlot
