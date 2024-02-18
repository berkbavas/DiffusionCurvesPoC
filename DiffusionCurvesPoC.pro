QT += gui xml

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES -= DEBUG

SOURCES += \
        ColorCurve.cpp \
        ColorPoints.cpp \
        ConstrainedImage.cpp \
        DiffusionCurveRenderer.cpp \
        Image.cpp \
        Main.cpp

HEADERS += \
    Bezier.h \
    ColorCurve.h \
    ColorPoints.h \
    Constants.h \
    ConstrainedImage.h \
    DiffusionCurveRenderer.h \
    Image.h \
    Structs.h \
    Utils.h
