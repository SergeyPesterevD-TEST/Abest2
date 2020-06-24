#ifndef _MODULE_GMACHINE_TYPES_H_
#define _MODULE_GMACHINE_TYPES_H_

#include "stdint.h"
#include "module_base_types.h"
#include "module_virtual_io_types.h"
#include "string.h"

namespace __ulp_m_gmachine{

class __CMD{
public:
	typedef enum{
		__GET_MACHINE_STATE = __ulp_module::__SHARED_CMD::__PRIVATE_CMD_START,
		__GET_RESULT,
		__GET_CYCLE_N,
		__GET_CURRENT_FRAME,
		__GET_CURRENT_FRAME_STRING,
		__GET_CURRENT_PROGRAM_N,
		__GET_PROGRAM_SPACE,
		__GET_PAGE_SIZE,
		__GET_MAX_PROGRAM,
		__START_PROGRAM,
		__START_PROGRAM_N,
		__STOP_PROGRAM,
		__PAUSE_PROGRAM,
		__GO_TO_NEXT_FRAME,
		__WRITE_PROGRAM_PARAM,
		__READ_PROGRAM_PARAM,
		__WRITE_PROGRAM_TO_BUFF,
		__WRITE_PROGRAM_BUFF_TO_FLASH,
		__CHECK_PROGRAM,
		__READ_PROGRAM,
		__SET_TMP_PARAM,
		__GET_TMP_PARAM,
		__LAST
	}__TYPEDEF;
};

class __STATE{
public:
	typedef enum{
		__PROGRAM_COMPLETE = 0,
		__CHECK_PROGRAM,
		__START_REF_SEARCH,
		__WAIT_REF_SEARCH,
		__READ_FRAME,
		__PROCESSING_FRAME,
		__WAIT_POSITION,
		__WAIT_TIME,
		__WAIT_IO_EXCHANGE,
		__WAIT_INPUT,
		__COMPLETE_FRAME,
		__PAUSE,
		__PROGRAM_ERROR,
		__PROGRAM_ABORT,
		__AUTO_STARTING,
		__UPD_CURRENT_POSITION,
		__SETTING_OFFSET,
		__WAIT_OFFSET_SET,
		__SETTING_GSYSTEM,
		__WAIT_GSYSTEM_SET,
		__LAST
	}__TYPEDEF;
};

class __RESULT{
public:
	typedef enum{
		__DONE = 0,
		__WORKING,
		__POSITIONING_ERROR,
		__CONNECTION_ERROR,
		__BROKEN_PROGRAM,
		__WRONG_SETTINGS,
		__ABORT,
		__LAST
	}__TYPEDEF;
};

class __RUN_MODE{
public:
	typedef enum{
		__AUTO = 0,
		__MANUAL,
		__LAST
	}__TYPEDEF;
};

class __AXIS_NAME{
public:
	typedef enum{
		__X = 0,
		__Y,
		__Z,
		__A,
		__B,
		__C,
		__LAST
	}__TYPEDEF;
};

class __AXIS_TYPE{
public:
	typedef enum{
		__NOT_USED = 0,
		__SELF,
		__SLAVE,
		__LAST
	}__TYPEDEF;
};

class __AXIS_PARAM_TYPEDEF{
public:
	__AXIS_TYPE::__TYPEDEF type;
	uint8_t addr;

	__AXIS_PARAM_TYPEDEF() : type(__AXIS_TYPE::__NOT_USED), addr(0){

	}

	void copy(const __AXIS_PARAM_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__AXIS_PARAM_TYPEDEF));
	}

	void copy(const __AXIS_PARAM_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if(type >= __AXIS_TYPE::__LAST) return false;

		return true;
	}

	void set_default(){
		__AXIS_PARAM_TYPEDEF();
	}
};

class __VERIFY_RESULT{
public:
	typedef enum{
		__SUCCESS = 0,
		__FAILURE,
		__LAST
	}__TYPEDEF;
};

class __REF_CHECK{
public:
	typedef enum{
		__IF_NOT_CAPTURED,
		__ALWAYS,
		__NOT_SEARCH,
		__LAST
	}__TYPEDEF;
};

template<uint8_t MAX_SELF_AXIS>
class __SETTINGS_TYPEDEF{
public:
	uint16_t cycles;
	uint16_t auto_start_delay;
	uint32_t emergency_outputs[__ulp_m_virtual_io::__DESTINATION::__LAST];
	__AXIS_PARAM_TYPEDEF axis[__AXIS_NAME::__LAST];
	__REF_CHECK::__TYPEDEF ref_check;
	bool auto_start;

	__SETTINGS_TYPEDEF() : cycles(1), auto_start_delay(0), auto_start(false), ref_check(__REF_CHECK::__NOT_SEARCH){
		for(uint8_t i = 0; i < (sizeof(emergency_outputs)/sizeof(emergency_outputs[0])); i++){
			emergency_outputs[i] = 0;
		}
	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}

	void copy(const __SETTINGS_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if(ref_check >= __REF_CHECK::__LAST) return false;

		for(uint8_t i = 0; i < (sizeof(axis) / sizeof(axis[0])); i++){
			if(!axis[i].check()) return false;
			if(axis[i].type == __AXIS_TYPE::__SELF & (axis[i].addr >= MAX_SELF_AXIS)) return false;
		}

		return true;
	}

	void set_default(){
		__SETTINGS_TYPEDEF();
	}
};

class __PROGRAMM_PARAM_TYPEDEF{
public:
	uint32_t size;
	uint16_t page;

	__PROGRAMM_PARAM_TYPEDEF() : size(0), page(0){

	}

	void copy(const __PROGRAMM_PARAM_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__PROGRAMM_PARAM_TYPEDEF));
	}

	void copy(const __PROGRAMM_PARAM_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		return true;
	}

	void set_default(){
		__PROGRAMM_PARAM_TYPEDEF();
	}
};

template<uint8_t N_MAX_PROG>
class __PROGRAMM_STRUCTURE_TYPEDEF{
public:
	__PROGRAMM_PARAM_TYPEDEF prog_param[N_MAX_PROG];

	uint8_t* get_ptr(){
		return reinterpret_cast<uint8_t*>(this);
	}

	uint8_t get_size() const{
		return sizeof(__PROGRAMM_STRUCTURE_TYPEDEF);
	}
};

class __PROGRAM_STATE_DATA_TYPEDEF{
public:
	char* program_ptr;
	uint16_t frame;
	uint32_t param;
	uint8_t prog;

	__PROGRAM_STATE_DATA_TYPEDEF() : program_ptr(0), frame(0), param(0), prog(0){

	}
};



}

#endif
