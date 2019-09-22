TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        DSString.cpp \
        DSVector.cpp \
        sentimentmain.cpp \
        test.cpp

HEADERS += \
    ../../../../Downloads/catch(1).hpp \
    ../../../../Downloads/catch.hpp \
    DSString.h \
    DSVector.h \
    catch.hpp \
    sentimentmain.h \
    test.h
