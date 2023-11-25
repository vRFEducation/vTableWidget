CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(vTableWidgetPlugin)
TEMPLATE    = lib

HEADERS     = vTableWidgetPlugin.h
SOURCES     = vTableWidgetPlugin.cpp
RESOURCES   = \
    vTableWidgetResource.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(vTableWidget.pri)
