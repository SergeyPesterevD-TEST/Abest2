#ifndef _MODULE_POSITIONER_TYPES_H_
#define _MODULE_POSITIONER_TYPES_H_

#include "stdint.h"
#include "module_base_types.h"
#include "string.h"

namespace __ulp_m_positioner{

class __CMD{
public:
	typedef enum: uint8_t{
		__START_REF_SEARCH = __ulp_module::__SHARED_CMD::__PRIVATE_CMD_START,
		__MOVE_TO,
		__MOVE_TO_W_SPEED,
		__STOP,
		__GET_CURRENT_STATE,
		__GET_CURRENT_RESULT,
		__GET_CURRENT_SPEED,
		__GET_CURRENT_DIRECTION,
		__GET_LINKED_SENSOR_ID,
		__LAST
	}__TYPEDEF;
};

class __MODE{
public:
	typedef enum : uint8_t{
	    __DISCRETE = 0,
		__PULSE,
		__LAST
	}__TYPEDEF;
};

class __STATE{
public:
	typedef enum : uint8_t{
		__STOP = 0,
		__WAIT_AXIS_SEL_SIGNAL,
		__RUN,
		__STOPPING,
		__BRAKING,
		__LAST
	}__TYPEDEF;
};

class __RESULT{
public:
	typedef enum : uint8_t{
	    __WORKING = 0,
		__REF_SEARCHING,
		__MANUAL,
	    __DONE,
	    __POSITIONING_ERROR,
	    __SENSOR_ERROR,
		__LIMITER_DETECT,
		__REF_NOT_CAPTURED,
		__STOP_CMD,
		__WRONG_DIRECTION,
		__NOT_MOVING,
		__INTERNAL_ERROR,
	    __LAST
	}__TYPEDEF;
};

class __MOVE_DIRECTION{
public:
	typedef enum : uint8_t{
	    __LEFT = 0,
	    __RIGHT,
	    __LAST
	}__TYPEDEF;
};

class __MOVING_TYPE{
public:
	typedef enum : uint8_t{
		__NORMAL,
		__BACKLASH,
		__EMERGENCY,
		__LAST
	}__TYPEDEF;
};

class __DESTINATION_TYPE{
public:
	typedef enum : uint8_t{
		__LIMITED,
		__ENDLESS,
		__LAST
	}__TYPEDEF;
};

class __REF_SEARCH_ACTION{
public:
	typedef enum : uint8_t{
		__MOVING_RIGHT = 0,
		__MOVING_LEFT,
		__SET_OFFSET,
		__NO_ACTION,
		__LAST
	}__TYPEDEF;
};

class __REF_SEARCH_CAPTURE{
public:
	typedef enum : uint8_t{
		__CAPTURE = 0,
		__CAPTURE_IN_REF_ZONE,
		__CAPTURE_NOT,
		__LAST
	}__TYPEDEF;
};

class __MOTION{
public:
	typedef enum : uint8_t{
		__OK,
		__NOT_MOVING,
		__WRONG_DIRECTION,
		__LAST
	}__TYPEDEF;
};

class __REF_SEARCH_CMD_TYPEDEF{
public:
	__REF_SEARCH_ACTION::__TYPEDEF cmd;
	__REF_SEARCH_CAPTURE::__TYPEDEF capture;
	uint16_t speed;

	__REF_SEARCH_CMD_TYPEDEF() :
		cmd(__REF_SEARCH_ACTION::__NO_ACTION), capture(__REF_SEARCH_CAPTURE::__CAPTURE_NOT),
		speed(0){

	}

	void copy(const __REF_SEARCH_CMD_TYPEDEF* const _other){
		cmd = _other->cmd;
		capture = _other->capture;
		speed = _other->speed;
	}

	void copy(const __REF_SEARCH_CMD_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if(cmd >= __REF_SEARCH_ACTION::__LAST) return false;
		if(capture >= __REF_SEARCH_CAPTURE::__LAST) return false;

		return true;
	}

	void set_default(){
		__REF_SEARCH_CMD_TYPEDEF();
	}
};

class __SETTINGS_TYPEDEF{
public:
	uint32_t positioning_tolerance;
	uint16_t backlash_speed;
	uint16_t max_speed;
	uint16_t manual_speed;
	uint16_t stop_detect_range;
	uint16_t stop_detect_time;
	uint16_t max_sens_series_error;
	uint16_t backlash_timeout;
	__REF_SEARCH_CMD_TYPEDEF ref_cmd[2];
	bool backlash;
	bool ena_axis_signal;

	__SETTINGS_TYPEDEF() : positioning_tolerance(5), backlash_speed(1), max_speed(3),
			manual_speed(2), stop_detect_range(2), stop_detect_time(100), max_sens_series_error(10),
			backlash(true), ena_axis_signal(false), backlash_timeout(10000){

	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}

	void copy(const __SETTINGS_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		for(uint8_t i = 0; i < (sizeof(ref_cmd) / sizeof(ref_cmd[0])); i++){
			if(!ref_cmd[i].check()) return false;
		}

		return true;
	}

	void set_default(){
		__SETTINGS_TYPEDEF();
	}
};

#pragma pack(push, 1)
class __MOVE_W_SPEED_CMD_DATA_TYPEDEF{
public:
	int64_t coordinate;
	uint16_t speed;

	void copy(const __MOVE_W_SPEED_CMD_DATA_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__MOVE_W_SPEED_CMD_DATA_TYPEDEF));
	}

	void copy(const __MOVE_W_SPEED_CMD_DATA_TYPEDEF _other){
		copy(&_other);
	}

	__MOVE_W_SPEED_CMD_DATA_TYPEDEF(){
		memset((void*)this, 0, sizeof(__MOVE_W_SPEED_CMD_DATA_TYPEDEF));
	}

	__MOVE_W_SPEED_CMD_DATA_TYPEDEF(const __MOVE_W_SPEED_CMD_DATA_TYPEDEF* const _other){
		copy(_other);
	}
};
#pragma pack(pop)

}


#endif
