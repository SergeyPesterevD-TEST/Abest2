#ifndef _MODULE_SYSTEM_TYPES_H_
#define _MODULE_SYSTEM_TYPES_H_

#include "module_base_types.h"
#include "module_sensor_types.h"

namespace __ulp_m_system{

class __CMD{
public:
	typedef enum{
		__GET_MODULES_NUM = __ulp_module::__SHARED_CMD::__PRIVATE_CMD_START,
		__GET_DEVICE_ID,
		__GET_HW_VER,
		__GET_SW_VER,
		__GET_SERIAL,
		__SAVE_SYSTEM_SETTINGS,
		__LOAD_SYSTEM_SETTINGS,
		__GET_SYSTEM_SETTINGS_STATE,
		__GET_SYSTEM_MODULE_STATE,
		__SET_MARK,
		__GET_LOG_DATA,
		__UPD_FIRMWARE = 0x70,
		__LAST
	}__TYPEDEF;
};

class __SETTINGS_TYPEDEF{
public:
	uint16_t processing_time_ms;

	__SETTINGS_TYPEDEF() : processing_time_ms(1){

	}

	void set_default(){
		processing_time_ms = 1;
	}

	bool check(){
		return true;
	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}

	void copy(const __SETTINGS_TYPEDEF _other){
		copy(&_other);
	}
};

typedef struct{
	uint16_t queue 	: 15;
	uint16_t overflow : 1;
}__LOG_DATA_TYPEDEF;

#pragma pack(push, 1)
typedef struct __SEND_LOG_DATA_TYPEDEF{
	union{
		__LOG_DATA_TYPEDEF status;
		uint16_t raw_status;
	};
	__ulp_m_sensor::__SENS_DATA_TYPEDEF data[26];
}__SEND_LOG_DATA_TYPEDEF;
#pragma pack(pop)

typedef uint16_t __PACKET_MARK_TYPEDEF;





}



#endif
