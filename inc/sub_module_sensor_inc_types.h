#ifndef _SUB_MODULE_SENSOR_INC_TYPES_H_
#define _SUB_MODULE_SENSOR_INC_TYPES_H_

#include "module_sensor_types.h"

namespace __ulp_sm_sensor_inc{

class __CMD{
public:
	typedef enum{
		__SEARCH_REF_POINT = __ulp_m_sensor::__CMD::__SUB_MODULE_CMD_START,
		__RESET_REF_POINT,
		__STOP_SEARCH_REF_POINT,
		__CLEAR_POSITION,
		__LAST
	}__TYPEDEF;
};

#pragma pack(push, 1)
class __SETTINGS_TYPEDEF{
public:
	bool ref_exist;
	bool ab_switch;
	bool use_filter;
	uint8_t filter_lvl;

	__SETTINGS_TYPEDEF() : ref_exist(false), ab_switch(false),
			use_filter(false), filter_lvl(0){

	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}

	void copy(const __SETTINGS_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if(filter_lvl >= 64) return false;

		return true;
	}

	void set_default(){
		__SETTINGS_TYPEDEF();
	}
};
#pragma pack(pop)

}



#endif
