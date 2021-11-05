QT += gui xml

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES -= DEBUG

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ColorCurve.cpp \
        ColorPoints.cpp \
        ConstrainedImage.cpp \
        DiffusionCurveRenderer.cpp \
        Image.cpp \
        Main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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
