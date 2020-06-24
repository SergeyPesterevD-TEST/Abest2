#ifndef _SUB_MODULE_SENSOR_BISS_TYPES_H_
#define _SUB_MODULE_SENSOR_BISS_TYPES_H_

#include "module_sensor_types.h"

namespace __ulp_sm_sensor_biss{

class __CMD{
public:
	typedef enum{
		__SEARCH_REF_POINT = __ulp_m_sensor::__CMD::__SUB_MODULE_CMD_START,
		__RESET_REF_POINT,
		__WRITE_EDS,
		__READ_EDS,
		__RUN_EXCHANGE_EDS,
		__GET_EXCHANGE_RESULT,
		__LAST
	}__TYPEDEF;
};

#pragma pack(push, 1)
class __SETTINGS_TYPEDEF{
public:
	uint8_t n_data_bits;
	uint8_t n_alarm_bits;
	uint8_t frequency;
	uint8_t crc_polinom;
	uint8_t start_crc_value;
	uint8_t alarm_inverse;
	bool revolution_calc;
	bool zero_shift;

	__SETTINGS_TYPEDEF() : n_data_bits(21), n_alarm_bits(2), frequency(1), crc_polinom(0x43), start_crc_value(0),
			alarm_inverse(0), revolution_calc(false), zero_shift(false){

	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}

	void copy(const __SETTINGS_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if((crc_polinom != 0x43) & (crc_polinom != 0x25)) return false;

		uint8_t crc_size;
		if(crc_polinom == 0x43) crc_size = 6;
		else crc_size = 5;

		if(n_data_bits < 1) return false;
		if((n_data_bits + n_alarm_bits + crc_size) > 64) return false;
		if(n_alarm_bits > 8) return false;
		if(frequency < 1) return false;
		if((crc_polinom != 0x43) & (crc_polinom != 0x25)) return false;
		if(start_crc_value > 15) return false;
		if((n_data_bits == 64) & revolution_calc) return false;

		return true;
	}

	void set_default(){
		__SETTINGS_TYPEDEF();
	}
};
#pragma pack(pop)

class __EDS_OPERATION{
public:
	typedef enum{
		__IDLE = 0,
		__WRITE,
		__READ,
		__CMD,
		__LAST
	}__TYPEDEF;
};

class __EDS_OPERATION_STATE{
public:
	typedef enum{
		__INIT_WAIT = 0,
		__CMD_SENDING,
		__DATA_SENDING,
		__OP_SUCCESS,
		__OP_FAILED,
		__LAST
	}__TYPEDEF;
};

typedef union{
	struct{
		uint32_t op		: 2;
		uint32_t crc	: 4;
		uint32_t addr	: 7;
		uint32_t id		: 3;
		uint32_t cts	: 1;
		uint32_t start 	: 1;
	} v;
	uint32_t buff;
}__REQUEST_CMD_TYPEDEF;

typedef union{
	struct{
		uint32_t p		: 1;
		uint32_t crc	: 4;
		uint32_t data	: 8;
		uint32_t s		: 1;
	} v;
	uint32_t buff;
}__REQUEST_DATA_TYPEDEF;

#pragma pack(push, 1)
class __EDS_EXCHANGE_CMD_TYPEDEF{
public:
	uint8_t id;
	__EDS_OPERATION::__TYPEDEF operation;
	uint8_t address;
	uint8_t reg_num;

	__EDS_EXCHANGE_CMD_TYPEDEF() : id(0), operation((__EDS_OPERATION::__IDLE)), address(0), reg_num(0){

	}

	void copy(const __EDS_EXCHANGE_CMD_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__EDS_EXCHANGE_CMD_TYPEDEF));
	}

	void copy(const __EDS_EXCHANGE_CMD_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if(id > 7) return false;
		if(operation >= __EDS_OPERATION::__LAST) return false;

		return true;
	}

	void set_default(){
		__EDS_EXCHANGE_CMD_TYPEDEF();
	}
};
#pragma pack(pop)

#pragma pack(push, 1)
template<uint8_t REG_NUM>
class __EDS_WRITE_CMD_TYPEDEF{
public:
	uint8_t start_addr;
	uint8_t reg_num;
	uint8_t reg_data[REG_NUM];

	__EDS_WRITE_CMD_TYPEDEF() : start_addr(0), reg_num(0){
		memset((void*)reg_data, 0, sizeof(reg_data));
	}

	void copy(const __EDS_WRITE_CMD_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__EDS_WRITE_CMD_TYPEDEF));
	}

	void copy(const __EDS_WRITE_CMD_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if(reg_num != REG_NUM) return false;

		return true;
	}

	void set_default(){
		__EDS_WRITE_CMD_TYPEDEF();
	}
};
#pragma pack(pop)


#pragma pack(push, 1)
class __EDS_READ_CMD_TYPEDEF{
public:
	uint8_t start_addr;
	uint8_t reg_num;

	__EDS_READ_CMD_TYPEDEF() : reg_num(0), start_addr(0){

	}

	void copy(const __EDS_READ_CMD_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__EDS_READ_CMD_TYPEDEF));
	}

	void copy(const __EDS_READ_CMD_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		return true;
	}

	void set_default(){
		__EDS_READ_CMD_TYPEDEF();
	}
};
#pragma pack(pop)

}

#endif
