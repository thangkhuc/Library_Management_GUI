QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    anzeige_dialog.cpp \
    book.cpp \
    cd.cpp \
    kunde.cpp \
    main.cpp \
    library.cpp \
    medien.cpp

HEADERS += \
    anzeige_dialog.h \
    book.h \
    cd.h \
    kunde.h \
    library.h \
    medien.h

FORMS += \
    anzeige_dialog.ui \
    library.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
