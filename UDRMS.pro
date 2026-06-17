QT += core gui widgets

CONFIG += c++17

TARGET = UDRMS
TEMPLATE = app

INCLUDEPATH += include gui

SOURCES += \
    src/main.cpp \
    src/Person.cpp \
    src/Student.cpp \
    src/Staff.cpp \
    src/DormAdministrator.cpp \
    src/RestaurantStaff.cpp \
    src/Room.cpp \
    src/Restaurant.cpp \
    src/Dormitory.cpp \
    src/University.cpp \
    src/DataManager.cpp \
    gui/MainWindow.cpp \
    gui/LoginDialog.cpp \
    gui/StudentDialog.cpp \
    gui/DormDialog.cpp \
    gui/RoomDialog.cpp \
    gui/RestaurantDialog.cpp

HEADERS += \
    include/Person.h \
    include/Student.h \
    include/Staff.h \
    include/DormAdministrator.h \
    include/RestaurantStaff.h \
    include/Room.h \
    include/Restaurant.h \
    include/Dormitory.h \
    include/University.h \
    include/DataManager.h \
    gui/MainWindow.h \
    gui/LoginDialog.h \
    gui/StudentDialog.h \
    gui/DormDialog.h \
    gui/RoomDialog.h \
    gui/RestaurantDialog.h