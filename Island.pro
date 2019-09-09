TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11

SOURCES +=  main.cpp field.cpp bot.cpp

HEADERS += field.h bot.h

include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    draft.txt \
    out.txt
