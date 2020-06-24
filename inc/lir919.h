#ifndef LIR919_H
#define LIR919_H

#include "link.h"
#include "link_types.h"

#include "packet.h"

//#include "d:\MyProg\git\919Libraries\software\embedded\ULP\inc\module_base_types.h"
#include "module_base_types.h"
//#include "system_mod.h"
//#include "sensor_mod.h"
//#include "io_mod.h"
//#include "rs485_mod.h"
//#include "virtualio_mod.h"
//#include "remap_mod.h"
//#include "positioner_mod.h"



class CLIR919{
private:
    _packet::CPacket tx;
    _packet::CPacket rx;
    _ulp_link::Clink_base* plink;

	void(*message_callback)(__ulp_module::__TYPE::__TYPEDEF& _module, _cmd::__CMD_TYPEDEF& _cmd);

	void(*callback_adapter)(__ulp_module::__TYPE::__TYPEDEF& _module, uint8_t _cmd, uint8_t* _ptr, uint8_t ndata_bytes);



	void exchange_read();
	void exchange_write();

    uint32_t link_error_cntr;
public:
    CLIR919();
    ~CLIR919();
	void exchange(uint32_t SleepTime = 0, bool ReadBeforeWrite = true);

    bool change_link(_ulp_link::__CONNECTION_TYPE_TYPEDEF _link);
    _ulp_link::__CONNECTION_STATE_TYPEDEF get_link_state();
    _ulp_link::__CONNECTION_TYPE_TYPEDEF get_link_type();
    uint32_t get_num_of_connected_devices();
	list<wstring> get_device_list()
	{
		return plink->get_device_list();
	}
    bool get_name_of_device(uint32_t _dev_num, std::wstring* _str);
    bool link_connect(uint8_t _device);
    bool link_disconnect();

	_ulp_link::Clink_base* get_link()
	{
		return plink;
	}

    template<class CMD_T, class DATA_T>
	bool send_message(__ulp_module::__TYPE::__TYPEDEF _module, CMD_T _command, DATA_T _data, uint32_t _data_size = sizeof(DATA_T)){
        return tx.add_message(_module, _command, &_data, _data_size);
    }

    template<class CMD_T>
	bool send_message(__ulp_module::__TYPE::__TYPEDEF _module, CMD_T _command){
        return tx.add_message(_module, _command);
    }

	bool send_message(__ulp_module::__TYPE::__TYPEDEF _module, uint8_t _command, uint8_t* _data, uint32_t _data_size);

    template<class T>
    bool change_link_settings(T _settings){
        return plink->set_settings(_settings);
    }

    bool change_link_settings(uint8_t* _settings, uint16_t _settings_size);

	void set_message_callback(void(*_f)(__ulp_module::__TYPE::__TYPEDEF& _module, _cmd::__CMD_TYPEDEF& _cmd));
	void set_message_callback_adapter(void(*_callback_adapter)(__ulp_module::__TYPE::__TYPEDEF& _module, uint8_t _cmd, uint8_t* _ptr, uint8_t ndata_bytes));
};

#endif // LIR919_H
