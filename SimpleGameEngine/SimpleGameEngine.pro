QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    cube.cpp \
    group.cpp \
    main.cpp \
    simpleobject3d.cpp \
    skybox.cpp \
    transformableObject.cpp \
    widget.cpp

HEADERS += \
    camera.h \
    cube.h \
    group.h \
    modelAssembling.h \
    simpleobject3d.h \
    skybox.h \
    transformableobject.h \
    vertexData.h \
    widget.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    shaders.qrc \
    textures.qrc


win32-g*
{
    LIBS += -lOpengl32
}


