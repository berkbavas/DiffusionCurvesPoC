QT += gui xml

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES -= DEBUG

SOURCES += \
        Sources/ColorCurve.cpp \
        Sources/ColorPoints.cpp \
        Sources/ConstrainedImage.cpp \
        Sources/DiffusionCurveRenderer.cpp \
        Sources/Image.cpp \
        Sources/Main.cpp

HEADERS += \
    Sources/Bezier.h \
    Sources/ColorCurve.h \
    Sources/ColorPoints.h \
    Sources/Constants.h \
    Sources/ConstrainedImage.h \
    Sources/DiffusionCurveRenderer.h \
    Sources/Image.h \
    Sources/Structs.h \
    Sources/Utils.h
