#ifndef _MODULE_SENSOR_TYPES_H_
#define _MODULE_SENSOR_TYPES_H_

#include "stdint.h"
#include "module_base_types.h"
#include "string.h"

namespace __ulp_m_sensor{

typedef union{
	struct{
		uint16_t alarm_bits			: 8;
		uint16_t sensor_error		: 1;
		uint16_t no_ref				: 1;
		uint16_t correction_error	: 1;
		uint16_t ref_capture		: 1;
		uint16_t sub_mod_op_code	: 4;
	};
	uint16_t all;
} __STATUS_TYPEDEF;

#pragma pack(push, 1)
class __SENS_DATA_TYPEDEF{
public:
	int64_t coordinate;
	__STATUS_TYPEDEF status;

	void copy(const __SENS_DATA_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SENS_DATA_TYPEDEF));
	}

	void copy(const __SENS_DATA_TYPEDEF _other){
		copy(&_other);
	}

	__SENS_DATA_TYPEDEF(){
		memset((void*)this, 0, sizeof(__SENS_DATA_TYPEDEF));
	}

	__SENS_DATA_TYPEDEF(const __SENS_DATA_TYPEDEF* const _other){
		copy(_other);
	}

};
#pragma pack(pop)

class __CMD{
public:
	typedef enum{
		__UPD_SENSOR_DATA = __ulp_module::__SHARED_CMD::__PRIVATE_CMD_START,
		__GET_SENSOR_DATA,
		__SET_CURRENT_G_SYSTEM,
		__GET_CURRENT_G_SYSTEM,
		__SET_OFFSET,
		__SET_OFFSET_MANUAL,
		__GET_OFFSET,
		__GET_SENSOR_ERRORS,
		__CLR_SENSOR_ERRORS_CNTR,
		__GET_LAST_ERROR_CODE,

		__INIT_CORRECTION_PROC = 50,
		__GET_CORRECTION_POINT_INFO,
		__GET_CORRECTION_POINT_NUM,
		__ADD_CORRECTION_POINT,
		__SAVE_CORRECTION_TABLE,
		__ABORT_CORRECTION_PROCESS,
		__DELETE_CORRECTION_POINT,
		__EDIT_CORRECTION_POINT,
		__ADD_CORRECTION_POINT_MANUAL,
		__LAST,

		__SUB_MODULE_CMD_START = 60,
	}__TYPEDEF;
};

class __G_SYSTEM{
public:
	typedef enum{
		__RAWCO,
		__G52,
		__G53,
		__G54,
		__LAST
	}__TYPEDEF;
};

class __AXIS{
public:
	typedef enum{
		__LINEAR,
		__ROTARY,
		__LAST
	} __TYPEDEF;
};

class __SUB_MODULE_TYPES{
public:
	typedef enum{
		__INCREMENTAL = 0,
		__SSI,
		__BISS,
		__LVDT,
		__LAST
	}__TYPEDEF;
};

#pragma pack(push, 1)
class __SETTINGS_TYPEDEF{
public:
	uint32_t A;
	uint32_t B;
	bool is_reverse;
	__AXIS::__TYPEDEF axis_type;
	int64_t offset;
	uint32_t ipr;
	bool grey_convert;

	__SETTINGS_TYPEDEF(){
		set_default();
	}

	void set_default(){
		A = 1;
		B = 1;
		is_reverse = false;
		axis_type = __AXIS::__LINEAR;
		offset = 0;
		ipr = 1;
		grey_convert = false;
	}

	bool check(){
		if(axis_type >= __AXIS::__LAST) return false;

		return true;
	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}
};
#pragma pack(pop)


}

#endif
