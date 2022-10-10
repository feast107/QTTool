QT -= gui
QT += network
TEMPLATE = lib
DEFINES += QTTOOL_LIBRARY

CONFIG += c++11
CONFIG += staticlib
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Implement/Linux/Desktop.cpp \
    Implement/Linux/Control.cpp \
    Implement/CMD.cpp \
    Implement/Directory.cpp \
    Implement/Http.cpp \
    Implement/File.cpp \
    Implement/Path.cpp

HEADERS += \
    Include/QtTool_global.h \
    Include/Linux/Desktop.h \
    Include/Linux/Control.h \
    Include/Directory.h \
    Include/Http.h \
    Include/File.h \
    Include/Path.h \
    Include/Task.hpp \
    Include/Thread.h \
    Include/CMD.h \
    Include/Tool.hpp

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
