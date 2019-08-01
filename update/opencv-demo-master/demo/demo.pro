QT += core
QT -= gui

TARGET = demo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test1.cpp \
    test2.cpp \
    test3.cpp \
    test4.cpp \
    test5.cpp \
    test6.cpp \
    test7.cpp

HEADERS += \
    test1.h \
    test2.h \
    test3.h \
    test4.h \
    test5.h \
    test6.h \
    test7.h

#头文件
INCLUDEPATH += /opt/opencv3.4/include
DEPENDPATH += /opt/opencv3.4/include

#opencv库
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_calib3d
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_core
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_dnn
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_features2d
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_flann
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_highgui
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_imgcodecs
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_imgproc
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_ml
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_objdetect
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_photo
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_shape

unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_stitching
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_superres
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_videoio
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_video
unix:!macx: LIBS += -L/opt/opencv3.4/lib/ -lopencv_videostab
