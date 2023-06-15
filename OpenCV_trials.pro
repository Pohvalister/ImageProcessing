QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
#QMAKE_LFLAGS += -static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += link_pkgconfig
PKGCONFIG += opencv libavcodec libavformat

#LIBS += -lopencv_core \
#        -lopencv_imgproc \
#        -lopencv_imgcodecs \
#        -lopencv_videoio \
#        -lopencv_video \
#        -lopencv_highgui \

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui
