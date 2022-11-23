#-------------------------------------------------
#
# Project created by QtCreator 2019-05-08T10:38:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qrdbtool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../eternity_common/BaseFile.cpp \
        ../eternity_common/BitStream.cpp \
        ../eternity_common/DOA6/G1tFile.cpp \
        ../eternity_common/DOA6/RdbFile.cpp \
        ../eternity_common/DOA6/RnkFile.cpp \
        ../eternity_common/DdsFile.cpp \
        ../eternity_common/FileStream.cpp \
        ../eternity_common/FixedBitStream.cpp \
        ../eternity_common/FixedMemoryStream.cpp \
        ../eternity_common/IniFile.cpp \
        ../eternity_common/MemoryStream.cpp \
        ../eternity_common/Stream.cpp \
        ../eternity_common/Utils.cpp \
        ../eternity_common/crypto/md5.c \
        ../eternity_common/crypto/rijndael.c \
        ../eternity_common/crypto/sha1.c \
        ../eternity_common/tinyxml/tinystr.cpp \
        ../eternity_common/tinyxml/tinyxml.cpp \
        ../eternity_common/tinyxml/tinyxmlerror.cpp \
        ../eternity_common/tinyxml/tinyxmlparser.cpp \
        debug.cpp \
        main.cpp \
        mainwindow.cpp \
        workerdialog.cpp

HEADERS += \
        ../eternity_common/BaseFile.h \
        ../eternity_common/BitStream.h \
        ../eternity_common/DOA6/G1tFile.h \
        ../eternity_common/DOA6/RdbFile.h \
        ../eternity_common/DOA6/RnkFile.h \
        ../eternity_common/DdsFile.h \
        ../eternity_common/FileStream.h \
        ../eternity_common/FixedBitStream.h \
        ../eternity_common/FixedMemoryStream.h \
        ../eternity_common/IniFile.h \
        ../eternity_common/MemoryStream.h \
        ../eternity_common/Stream.h \
        ../eternity_common/Utils.h \
        ../eternity_common/common.h \
        ../eternity_common/crypto/md5.h \
        ../eternity_common/crypto/rijndael.h \
        ../eternity_common/crypto/sha1.h \
        ../eternity_common/debug.h \
        ../eternity_common/tinyxml/tinystr.h \
        ../eternity_common/tinyxml/tinyxml.h \
        ../eternity_common/vs/dirent.h \
        mainwindow.h \
        workerdialog.h

FORMS += \
        mainwindow.ui \
        workerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += ../eternity_common

QMAKE_CXXFLAGS += -DTIXML_USE_STL -DDIRECTX_TEX_SUPPORT
LIBS += -lzlib -lversion -ladvapi32 -lshell32 -luser32 -ld3d11 -lole32 -lwindowscodecs -luuid -lDirectXTex
#LIBS += -L"C:\fbxsdk\lib\vs2015\x64\release"
CONFIG+=resources_big

win32:RC_ICONS += HON.ico

DISTFILES +=
