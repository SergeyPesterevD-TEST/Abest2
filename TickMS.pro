QT      += serialbus core gui
QT      += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

#LIBS += "rfdevice_mingwd.dll"
#LIBS += "ulp_lib.dll"
#LIBS += "owen_io.dll"

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
    ModBusMaster.cpp \
    RF603.cpp \
    SQLmodule.cpp \
    inisettings.cpp \
    main.cpp \
    mainwindow.cpp \
    newrulondialog.cpp \
    qcustomplot.cpp \
    rfthread.cpp \
    sqlfilter.cpp \
    tsetupform.cpp

HEADERS += \
    ModBusMaster.h \
    RF603.h \
    RFheaders/RF060Device.h \
    RFheaders/RF085Device.h \
    RFheaders/RF096Device.h \
    RFheaders/RF256Device.h \
    RFheaders/RF25xDevice.h \
    RFheaders/RF603BDevice.h \
    RFheaders/RF603Device.h \
    RFheaders/RF603HSDevice.h \
    RFheaders/RF605Device.h \
    RFheaders/RF60xDevice.h \
    RFheaders/RF620Device.h \
    RFheaders/RF625DDevice.h \
    RFheaders/RF625Device.h \
    RFheaders/RF625Device_Legacy.h \
    RFheaders/RF651Device.h \
    RFheaders/RF656Device.h \
    RFheaders/RF65xDevice.h \
    RFheaders/RF65xNDevice.h \
    RFheaders/RF711Device.h \
    RFheaders/RFDevice.h \
    RFheaders/RFEthernetDetector.h \
    RFheaders/RFEthernetDevice.h \
    RFheaders/RFQDPMotorDevice.h \
    RFheaders/RFSerialDevice.h \
    RFheaders/RFString.h \
    RFheaders/RFTypeDefs.h \
    RFheaders/linuxTypeDefs.h \
    RFheaders/serial.h \
    SQLmodule.h \
    inc/cmd.h \
    inc/cmd_types.h \
    inc/config.h \
    inc/crc.h \
    inc/device_info_types.h \
    inc/hidapi.h \
    inc/libserialport.h \
    inc/libserialport_internal.h \
    inc/link.h \
    inc/link_types.h \
    inc/lir919.h \
    inc/module_base_types.h \
    inc/module_func_remap_types.h \
    inc/module_gmachine_types.h \
    inc/module_io_types.h \
    inc/module_positioner_types.h \
    inc/module_rs485_types.h \
    inc/module_sensor_types.h \
    inc/module_system_types.h \
    inc/module_virtual_io_types.h \
    inc/module_zone_types.h \
    inc/packet.h \
    inc/qhidapi.h \
    inc/sub_module_base_types.h \
    inc/sub_module_positioner_discrete_types.h \
    inc/sub_module_rs485_modbus_types.h \
    inc/sub_module_rs485_sppu_types.h \
    inc/sub_module_sensor_biss_types.h \
    inc/sub_module_sensor_inc_types.h \
    inc/sub_module_sensor_ssi_types.h \
    inc/ulp_lib.h \
    inc/ulp_tools.h \
    inisettings.h \
    mainwindow.h \
    newrulondialog.h \
    owen/owen_io.h \
    qcustomplot.h \
    rfthread.h \
    sqlfilter.h \
    tsetupform.h

FORMS += \
    mainwindow.ui \
    newrulondialog.ui \
    sqlfilter.ui \
    tsetupform.ui

TRANSLATIONS += \
    TickMS_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# OWEN
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/owen/ -lowen_io
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/owen/ -lowen_io
else:unix: LIBS += -L$$PWD/owen/ -lowen_io

INCLUDEPATH += $$PWD/owen
DEPENDPATH += $$PWD/owen
# !OWEN

# RIFTEK
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/RFlib/ -lrfdevice_mingw
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/RFlib/ -lrfdevice_mingwd
else:unix: LIBS += -L$$PWD/RFlib/ -lrfdevice_mingw

INCLUDEPATH += $$PWD/RFlib
DEPENDPATH += $$PWD/RFlib
# !RIFTEK

DISTFILES += \
    algorithms/.gitignore \
    algorithms/algorithms.pri
