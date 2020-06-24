#ifndef _SUB_MODULE_SENSOR_SSI_TYPES_H_
#define _SUB_MODULE_SENSOR_SSI_TYPES_H_

#include "module_sensor_types.h"

namespace __ulp_sm_sensor_ssi{

class __CMD{
public:
	typedef enum{
		__SEARCH_REF_POINT = __ulp_m_sensor::__CMD::__SUB_MODULE_CMD_START,
		__RESET_REF_POINT,
		__LAST
	}__TYPEDEF;
};

#pragma pack(push, 1)
class __SETTINGS_TYPEDEF{
public:
	uint16_t alarm_invert;
	uint8_t n_data_bits;
	uint8_t n_alarm_bits;
	uint8_t first_data_bit_pos;
	uint8_t frequency;
	uint8_t start_interval;
	bool double_read;
	bool revolution_calc;
	bool zero_shift;
	bool alarm_slope_check;

	__SETTINGS_TYPEDEF() : alarm_invert(0), n_data_bits(24), n_alarm_bits(0), first_data_bit_pos(0), frequency(1),
							start_interval(0), double_read(true), revolution_calc(false), zero_shift(false), alarm_slope_check(false){

	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}

	void copy(const __SETTINGS_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if(n_data_bits + n_alarm_bits > 64) return false;
		if(n_alarm_bits > 16) return false;
		if(first_data_bit_pos > n_alarm_bits) return false;
		if(n_data_bits < 1) return false;
		if((n_data_bits == 64) & revolution_calc) return false;

		return true;
	}

	void set_default(){
		__SETTINGS_TYPEDEF();
	}
};
#pragma pack(pop)






}




#endif
