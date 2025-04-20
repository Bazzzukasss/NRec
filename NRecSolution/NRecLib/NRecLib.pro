TEMPLATE = lib
CONFIG += staticlib c++17
DESTDIR = ../bin

SOURCES += \
	NRecLib.cpp

HEADERS += \
	NRecLib.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
