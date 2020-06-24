#ifndef _MODULE_FUNC_REMAP_TYPES_H_
#define _MODULE_FUNC_REMAP_TYPES_H_

#include "stdint.h"
#include "module_base_types.h"
#include "module_virtual_io_types.h"
#include "string.h"

namespace __ulp_m_func_remap{

typedef void(__IN_FUNC_PTR_TYPEDEF)(bool);
typedef bool(__OUT_FUNC_PTR_TYPEDEF)(void);

class __IN_FUNCTION_SETTINGS{
public:
    bool ena;
    __ulp_m_virtual_io::__IN_SOURCE_TYPEDEF src;

    __IN_FUNCTION_SETTINGS() : ena(false), src(){

    }

    void copy(const __IN_FUNCTION_SETTINGS _other){
    	copy(&_other);
    }

    void copy(const __IN_FUNCTION_SETTINGS* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__IN_FUNCTION_SETTINGS));
	}

    bool check(){
    	if(!src.check()) return false;

    	return true;
    }

    void set_default(){
    	__IN_FUNCTION_SETTINGS();
    }
};

class __OUT_FUNCTION_SETTINGS{
public:
    bool ena;
    __ulp_m_virtual_io::__OUT_DESTINATION_TYPEDEF dst;

    __OUT_FUNCTION_SETTINGS() : ena(false), dst(){

    }

    void copy(const __OUT_FUNCTION_SETTINGS _other){
    	copy(&_other);
    }

    void copy(const __OUT_FUNCTION_SETTINGS* const _other){
    	memcpy((void*)this, (void*)_other, sizeof(__OUT_FUNCTION_SETTINGS));
	}

    bool check(){
    	if(!dst.check()) return false;

    	return true;
    }

    void set_default(){
    	__OUT_FUNCTION_SETTINGS();
    }
};

class __INTERCONNECT_FUNCTION_SETTINGS{
public:
    bool ena;
    __ulp_m_virtual_io::__IN_SOURCE_TYPEDEF src;
    __ulp_m_virtual_io::__OUT_DESTINATION_TYPEDEF dst;

    __INTERCONNECT_FUNCTION_SETTINGS() : ena(false), src(), dst(){

    }

    void copy(const __INTERCONNECT_FUNCTION_SETTINGS _other){
    	copy(&_other);
    }

    void copy(const __INTERCONNECT_FUNCTION_SETTINGS* const _other){
    	memcpy((void*)this, (void*)_other, sizeof(__INTERCONNECT_FUNCTION_SETTINGS));
    }

    bool check(){
    	if(!src.check()) return false;
    	if(!dst.check()) return false;

    	return true;
    }

    void set_default(){
    	__INTERCONNECT_FUNCTION_SETTINGS();
    }
};

class __IN_FUNCTION_ID{
public:
	typedef enum : uint8_t{
	    __LOG_WRITE = 0,
	    __REF_ZONE,
	    __SET_ZERO,
	    __LIMITER_POS,
	    __LIMITER_NEG,
	    __STOP_PRG,
	    __START_PRG,
	    __PAUSE_PRG,
	    __SELECT_AXIS,
		__REF_CAPTURE,
		__HAND_LEFT,
		__HAND_RIGHT,
	    __LAST
	}__TYPEDEF;
};

class __OUT_FUNCTION_ID{
public:
	typedef enum : uint8_t{
	    __SENS_ERROR,
	    __LINK_ERROR,
	    __LOG_OVERFLOW,
	    __MOTOR_RUN,
	    __MOTOR_BRAKE,
	    __MOTOR_DIRECTION,
	    __MOTOR_RUN_POS,
	    __MOTOR_RUN_NEG,
	    __MOTOR_SPEED1,
	    __MOTOR_SPEED2,
	    __MOTOR_SPEED3,
		__WRONG_POSITION,
	    __REF_NOT_CAPTURED,
	    __PRG_ERROR,
		__ZONE1,
		__ZONE2,
		__ZONE3,
		__ZONE4,
		__SELECT_AXIS,
	    __LAST
	}__TYPEDEF;
};

class __INTERCONNECT_FUNCTION_ID{
public:
	typedef enum : uint8_t{
	    __FUNC1,
	    __FUNC2,
	    __FUNC3,
	    __FUNC4,
	    __LAST
	}__TYPEDEF;
};

template<uint8_t IN_FUNC_NUM, uint8_t OUT_FUNC_NUM, uint8_t IC_FUNC_NUM>
class __SETTINGS_TYPEDEF{
public:
    __IN_FUNCTION_SETTINGS in[IN_FUNC_NUM];
    __OUT_FUNCTION_SETTINGS out[OUT_FUNC_NUM];
    __INTERCONNECT_FUNCTION_SETTINGS ic[IC_FUNC_NUM];

    __SETTINGS_TYPEDEF(){
    	set_default();
    }

    void copy(const __SETTINGS_TYPEDEF* const _other){
    	memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
    }

    void copy(const __SETTINGS_TYPEDEF _other){
    	copy(&_other);
	}

    bool check(){
    	for(uint8_t i = 0; i < (sizeof(in) / sizeof(in[0])); i++){
    		if(!in[i].check()) return false;
    	}

    	for(uint8_t i = 0; i < (sizeof(out) / sizeof(out[0])); i++){
    		if(!out[i].check()) return false;
    	}

    	for(uint8_t i = 0; i < (sizeof(ic) / sizeof(ic[0])); i++){
    		if(!ic[i].check()) return false;
    	}

    	return true;
    }

    void set_default(){
    	for(uint8_t i = 0; i < (sizeof(in) / sizeof(in[0])); i++){
			in[i].set_default();
		}

		for(uint8_t i = 0; i < (sizeof(out) / sizeof(out[0])); i++){
			out[i].set_default();
		}

		for(uint8_t i = 0; i < (sizeof(ic) / sizeof(ic[0])); i++){
			ic[i].set_default();
		}
    }
};


}


#endif
