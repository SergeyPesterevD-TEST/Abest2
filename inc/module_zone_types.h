#ifndef _MODULE_ZONE_TYPES_H_
#define _MODULE_ZONE_TYPES_H_

#include "module_base_types.h"
#include "module_sensor_types.h"
#include "stdint.h"
#include "string.h"

namespace __ulp_m_zone{

class __MODE{
public:
	typedef enum{
		__ZONE = 0,
		__CROSS_POINT,
		__LAST
	}__TYPEDEF;
};

class __ZONE_TYPEDEF{
public:
	int64_t coord1;
	int64_t coord2;
	__MODE::__TYPEDEF mode;
	__ulp_m_sensor::__G_SYSTEM::__TYPEDEF gsys;

	__ZONE_TYPEDEF() : coord1(0), coord2(0), mode(__MODE::__LAST), gsys(__ulp_m_sensor::__G_SYSTEM::__LAST){

	}

	void copy(const __ZONE_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__ZONE_TYPEDEF));
	}

	void copy(const __ZONE_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if(mode >= __MODE::__LAST) return false;
		if(gsys > __ulp_m_sensor::__G_SYSTEM::__LAST) return false;
		if(coord2 < coord1) return false;

		return true;
	}

	void set_default(){
		__ZONE_TYPEDEF();
	}
};

template<uint8_t ZONE_NUM>
class __SETTINGS_TYPEDEF{
public:
	__ZONE_TYPEDEF zone[ZONE_NUM];

	__SETTINGS_TYPEDEF(){

	}

	void set_default(){
		for(uint8_t i = 0; i < ZONE_NUM; i++){
			zone[i].set_default();
		}
	}

	bool check(){
		for(uint8_t i = 0; i < ZONE_NUM; i++){
			if(!zone[i].check()) return false;
		}

		return true;
	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}

	void copy(const __SETTINGS_TYPEDEF _other){
		copy(&_other);
	}
};

}

#endif
