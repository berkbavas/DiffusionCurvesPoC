QT += gui xml

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES -= DEBUG

SOURCES += \
        Source/ColorCurve.cpp \
        Source/ColorPoints.cpp \
        Source/ConstrainedImage.cpp \
        Source/DiffusionCurveRenderer.cpp \
        Source/Image.cpp \
        Source/Main.cpp

HEADERS += \
    Source/Bezier.h \
    Source/ColorCurve.h \
    Source/ColorPoints.h \
    Source/Constants.h \
    Source/ConstrainedImage.h \
    Source/DiffusionCurveRenderer.h \
    Source/Image.h \
    Source/Structs.h \
    Source/Utils.h
