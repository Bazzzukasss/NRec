QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DESTDIR = ../bin

SOURCES += \
    Models/ApplicationModel.cpp \
    Models/ComponentListModel.cpp \
    Models/ComponentModel.cpp \
    ViewModels/ApplicationViewModel.cpp \
    ViewModels/ComponentViewModel.cpp \
    Views/ApplicationView.cpp \
    Views/ComponentView.cpp \
    Views/CustomWidgets.cpp \
    main.cpp

HEADERS += \
    Models/ApplicationModel.h \
    Models/ComponentListModel.h \
    Models/ComponentModel.h \
    ViewModels/ApplicationViewModel.h \
    ViewModels/ComponentViewModel.h \
    Views/ApplicationView.h \
    Views/ComponentView.h \
    Views/CustomWidgets.h

FORMS += \ 

INCLUDEPATH += inc $$PWD/../NRecLib

LIBS *= -L$$OUT_PWD/$$DESTDIR -lNRecLib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
