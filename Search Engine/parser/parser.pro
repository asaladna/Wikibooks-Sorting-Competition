TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    dochandler.cpp \
    cleantext.cpp \
    avlhandler.cpp \
    hashhandler.cpp \
    hashtable.cpp \
    queryengine.cpp \
    indexHandler.cpp \
    relevancy.cpp \
    userinterface.cpp \
    search.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    rapidxml_iterators.hpp \
    rapidxml_print.hpp \
    rapidxml.hpp \
    rapidxml-1.13/rapidxml_iterators.hpp \
    rapidxml-1.13/rapidxml_print.hpp \
    rapidxml-1.13/rapidxml_utils.hpp \
    rapidxml-1.13/rapidxml.hpp \
    dochandler.h \
    cleantext.h \
    stem/common_lang_constants.h \
    stem/english_stem.h \
    stem/meta.h \
    stem/punctuation.h \
    stem/stemming.h \
    stem/string_util.h \
    stem/utilities.h \
    avlhandler.h \
    dsexceptions.h \
    AvlTree.h \
    hashtable.h \
    hashhandler.h \
    indexinput.h \
    queryengine.h \
    indexHandler.h \
    userinterface.h \
    relevancy.h \
    search.h

DISTFILES += \
    file.xml

