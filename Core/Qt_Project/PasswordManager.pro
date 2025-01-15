QT       += core gui
QT       += sql
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 添加头文件搜索路径
INCLUDEPATH += ../ThirdParty/QtCrypto \
                ../Inc

LIBS += -L ../ThirdParty/Dll -lqca-qt6
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Src/AddPasswordWindow.cpp \
    ../Src/BytesModel.cpp \
    ../Src/LoginDialog.cpp \
    ../Src/MainWindow.cpp \
    ../Src/PasswordDisplayItem.cpp \
    ../Src/PasswordListItem.cpp \
    ../Src/SerialWindow.cpp \
    ../Src/UpdateInput.cpp \
    ../Src/ViewModel.cpp \
    ../Src/main.cpp

HEADERS += \
    ../Inc/AddPasswordWindow.h \
    ../Inc/BytesModel.h \
    ../Inc/LoginDialog.h \
    ../Inc/MainWindow.h \
    ../Inc/PasswordDisplayItem.h \
    ../Inc/PasswordListItem.h \
    ../Inc/SerialWindow.h \
    ../Inc/UI_Headers/ui_AddPasswordWindow.h \
    ../Inc/UI_Headers/ui_LoginDialog.h \
    ../Inc/UI_Headers/ui_MainWindow.h \
    ../Inc/UI_Headers/ui_PasswordDisplayItem.h \
    ../Inc/UI_Headers/ui_PasswordListItem.h \
    ../Inc/UI_Headers/ui_SerialWindow.h \
    ../Inc/UI_Headers/ui_UpdateInput.h \
    ../Inc/UpdateInput.h \
    ../Inc/ViewModel.h

FORMS += \
    ../UI/AddPasswordWindow.ui \
    ../UI/LoginDialog.ui \
    ../UI/MainWindow.ui \
    ../UI/PasswordDisplayItem.ui \
    ../UI/PasswordListItem.ui \
    ../UI/SerialWindow.ui \
    ../UI/UpdateInput.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc
