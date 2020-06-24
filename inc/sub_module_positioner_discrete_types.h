#ifndef _SUB_MODULE_POSITIONER_DISCRETE_TYPES_H_
#define _SUB_MODULE_POSITIONER_DISCRETE_TYPES_H_

#include "module_positioner_types.h"

namespace __ulp_sm_positioner_discrete{

class __SPEED_LEVEL{
public:
	typedef enum{
		__BRAKE = 0,
	    __STOP,
	    __FIRST,
	    __SECOND,
	    __THREE,
	    __LAST
	}__TYPEDEF;
};


class __SETTINGS_TYPEDEF{
public:
	uint32_t stop_zone[__SPEED_LEVEL::__LAST - 1];

	__SETTINGS_TYPEDEF(){
		set_default();
	}

	void copy(const __SETTINGS_TYPEDEF _other){
		copy(&_other);
	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}

	bool check(){
		for(uint8_t i = 1; i < (__SPEED_LEVEL::__LAST - 1); i++){
			if(stop_zone[i] < stop_zone[i - 1]) return false;
		}
		return true;
	}

	void set_default(){
		for(uint8_t i = 0; i < (__SPEED_LEVEL::__LAST - 1); i++){
			stop_zone[i] = 0;
		}
	}
};



}



#endif
