TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        DSString.cpp \
        main.cpp \
        sentimentmain.cpp \
        tests.cpp

HEADERS += \
    ../../../../Downloads/catch(1).hpp \
    ../../../../Downloads/catch.hpp \
    DSString.h \
    DSVector.h \
    catch.hpp \
    sentimentmain.h
