QT += quick widgets
#charts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/filemanager.cpp \
        source/main.cpp \
        source/processmanager.cpp \
        source/progressbarprocess.cpp \
        source/qmlviewmanager.cpp \
        source/sortfiltermodel.cpp \
        source/wordcounter.cpp \
        source/wordstats.cpp \
        source/wordstatsmodel.cpp \
        source/wordstatsprocessor.cpp \


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    source/filemanager.h \
    source/processmanager.h \
    source/progressbarprocess.h \
    source/qmlviewmanager.h \
    source/sortfiltermodel.h \
    source/wordcounter.h \
    source/wordstats.h \
    source/wordstatsmodel.h \
    source/wordstatsprocessor.h
