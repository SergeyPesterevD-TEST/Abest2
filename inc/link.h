#ifndef LINK_H
#define LINK_H

#include "stdint.h"
#include "link_types.h"
//
#include "libserialport.h"
#include "libserialport_internal.h"


#include "crc.h"
#include <list>
#include <vector>
#include <string>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include "qhidapi.h"

namespace _ulp_link {

#define SP_TIMEOUT 200



class Clink_base{
protected:
    __CONNECTION_STATE_TYPEDEF connection_status;
    __CONNECTION_TYPE_TYPEDEF type;
    list<wstring> device_list ;

    virtual bool set_settings_ll(uint8_t* _settings_ptr, uint16_t _settings_size) = 0;
public:
    Clink_base(__CONNECTION_TYPE_TYPEDEF _type);
    virtual ~Clink_base();

    virtual bool connect(uint8_t _device) = 0;
    virtual bool disconnect() = 0;
	virtual void device_list_update() = 0;
    virtual bool write(uint8_t* buff, uint32_t size) = 0;
    virtual uint32_t read(uint8_t* buff) = 0;

    __CONNECTION_STATE_TYPEDEF get_status();
    __CONNECTION_TYPE_TYPEDEF get_type();
    bool set_settings(uint8_t* _settings, uint16_t _settings_size);
    uint32_t get_device_count();
    bool get_device_name(uint32_t _dev_num, std::wstring* _str);
	list<wstring> get_device_list();

    template<class T>
    bool set_settings(T _settings, uint16_t _settings_size = sizeof(T)){
        return set_settings_ll(reinterpret_cast<uint8_t*>(&_settings), _settings_size);
    }   
};


class Clink_com : public Clink_base{
private:
	sp_port *cur_cport;
	sp_port **aviable_ports;

	uint8_t device_addr;



    //QVector<QSerialPortInfo> com_devs;
   // vector<QSerialPortInfo> com_devs;

    bool set_settings_ll(uint8_t* _settings_ptr, uint16_t _settings_size);
public:
    Clink_com();
    ~Clink_com();
    void device_list_update();
    bool connect(uint8_t _device);
    bool disconnect();
    bool write(uint8_t* buff, uint32_t size);
    uint32_t read(uint8_t* buff);
};

class Clink_usb : public Clink_base{
private:
    QHidApi usb_port;
    bool set_settings_ll(uint8_t* _settings_ptr, uint16_t _settings_size);
public:
    Clink_usb();
    ~Clink_usb();
    void device_list_update();
    bool connect(uint8_t _device);
    bool disconnect();
    bool write(uint8_t* buff, uint32_t size);
    uint32_t read(uint8_t* buff);
};

}

#endif

