QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    XMLTree.cpp \
    XML_Correction.cpp \
    XML_Detection.cpp \
    compression.cpp \
    jsonconverter.cpp \
    main.cpp \
    mainwindow.cpp \
    xml_formating.cpp \
    xml_parser.cpp

HEADERS += \
    XMLTree.h \
    XML_Correction.h \
    XML_Detection.h \
    compression.h \
    jsonconverter.h \
    main.h \
    mainwindow.h \
    xml_formating.h \
    xml_parser.h

FORMS += \
    mainwindow.ui
RC_ICONS = xml.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Rcs.qrc

