#ifndef __MODULE_VIRTUAL_IO_TYPES_H_
#define __MODULE_VIRTUAL_IO_TYPES_H_

#include "stdint.h"
#include "module_base_types.h"
#include "string.h"

namespace __ulp_m_virtual_io{

class __CMD{
public:
	typedef enum{
		__GET_IO_NUM = __ulp_module::__SHARED_CMD::__PRIVATE_CMD_START,
		__GET_INPUTS_STATE,
		__GET_OUTPUTS_STATE,
		__LAST
	}__TYPEDEF;
};

class __TRIGGERS{
public:
	typedef enum: uint8_t{
		__HIGHL_LEVEL = 0,
		__LOW_LEVEL,
		__EDGE,
		__RISING_EDGE,
		__FALLING_EDGE,
		__LAST_LEVEL,
		__LAST
	}__TYPEDEF;
};

class __SOURCE{
public:
	typedef enum : uint8_t{
		__SELF_INPUTS = 0,
		__EXT_INPUTS,
		__LOG_INPUTS,
		__TIMERS,
		__LAST
	}__TYPEDEF;
};

class __DESTINATION{
public:
	typedef enum : uint8_t{
		__SELF_OUTPUTS = 0,
		__EXT_OUTPUTS,
		__LOG_OUTPUTS,
		__LAST
	}__TYPEDEF;
};

class __LOGIC_FUNCTION{
public:
	typedef enum : uint8_t{
		__AND = 0,
		__OR,
		__XOR,
		__EQ,
		__LAST
	}__TYPEDEF;
};

class __INPUTS_SETTINGS_TYPEDEF{
public:
    uint32_t inverse;
    uint32_t fix_high;

    __INPUTS_SETTINGS_TYPEDEF() : inverse(0), fix_high(0){

    }

    void copy(const __INPUTS_SETTINGS_TYPEDEF _other){
    	copy(&_other);
    }

    void copy(const __INPUTS_SETTINGS_TYPEDEF* const _other){
    	memcpy((void*)this, (void*)_other, sizeof(__INPUTS_SETTINGS_TYPEDEF));
    }

    bool check(){
    	return true;
    }

    void set_default(){
    	__INPUTS_SETTINGS_TYPEDEF();
    }
};

class __IN_SOURCE_TYPEDEF{
public:
    __SOURCE::__TYPEDEF src;
    __TRIGGERS::__TYPEDEF trg;
    uint8_t addr;

    __IN_SOURCE_TYPEDEF() : addr(0), src(__SOURCE::__SELF_INPUTS), trg(__TRIGGERS::__HIGHL_LEVEL){

    }

    void copy(const __IN_SOURCE_TYPEDEF* const _other){
    	memcpy((void*)this, (void*)_other, sizeof(__IN_SOURCE_TYPEDEF));
    }

    void copy(const __IN_SOURCE_TYPEDEF _other){
    	copy(&_other);
    }

    bool check(){
    	if(src >= __SOURCE::__LAST) return false;
    	if(trg >= __TRIGGERS::__LAST) return false;
    	if(addr >= 32) return false;

    	return true;
    }

    void set_default(){
    	__IN_SOURCE_TYPEDEF();
    }
};

class __OUT_DESTINATION_TYPEDEF{
public:
    __DESTINATION::__TYPEDEF dst;
    uint8_t addr;

    __OUT_DESTINATION_TYPEDEF() : dst(__DESTINATION::__SELF_OUTPUTS), addr(0){

    }

    void copy(const __OUT_DESTINATION_TYPEDEF* const _other){
    	memcpy((void*)this, (void*)_other, sizeof(__OUT_DESTINATION_TYPEDEF));
    }

    void copy(const __OUT_DESTINATION_TYPEDEF _other){
    	copy(&_other);
    }

    bool check(){
    	if(dst >= __DESTINATION::__LAST) return false;
    	if(addr >= 32) return false;

    	return true;
    }

    void set_default(){
    	__OUT_DESTINATION_TYPEDEF();
    }
};

class __LOGIC_INPUTS_SETTINGS_TYPEDEF{
public:
    bool ena;
    __IN_SOURCE_TYPEDEF src1;
    __LOGIC_FUNCTION::__TYPEDEF logic;
    __IN_SOURCE_TYPEDEF src2;

    __LOGIC_INPUTS_SETTINGS_TYPEDEF() : ena(false), src1(), src2(), logic(__LOGIC_FUNCTION::__OR){

    }

    void copy(const __LOGIC_INPUTS_SETTINGS_TYPEDEF _other){
    	copy(&_other);
    }

    void copy(const __LOGIC_INPUTS_SETTINGS_TYPEDEF* const _other){
    	memcpy((void*)this, (void*)_other, sizeof(__LOGIC_INPUTS_SETTINGS_TYPEDEF));
	}

    bool check(){
    	if(!src1.check() | !src2.check()) return false;
    	if(logic >= __LOGIC_FUNCTION::__LAST) return false;

    	return true;
    }

    void set_default(){
    	__LOGIC_INPUTS_SETTINGS_TYPEDEF();
    }
};

class __TIMERS_SETTINGS_TYPEDEF{
public:
    uint32_t max_cntr;
    bool pulse;

    __TIMERS_SETTINGS_TYPEDEF() : max_cntr(0), pulse(false){

    }

    void copy(const __TIMERS_SETTINGS_TYPEDEF _other){
    	copy(&_other);
    }

    void copy(const __TIMERS_SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__TIMERS_SETTINGS_TYPEDEF));
	}

    bool check(){
    	return true;
    }

    void set_default(){
    	__TIMERS_SETTINGS_TYPEDEF();
    }
};

class __OUTPUT_SETTINGS_TYPEDEF{
public:
	uint32_t inverse;

	__OUTPUT_SETTINGS_TYPEDEF() : inverse(0){

	}

	void copy(const __OUTPUT_SETTINGS_TYPEDEF _other){
		copy(&_other);
	}

	void copy(const __OUTPUT_SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__OUTPUT_SETTINGS_TYPEDEF));
	}

	bool check(){
		return true;
	}

	void set_default(){
		__OUTPUT_SETTINGS_TYPEDEF();
	}
};

class __LOGIC_OUTPUT_SETTINGS_TYPEDEF{
public:
	bool ena;
	__LOGIC_FUNCTION::__TYPEDEF logic;
	__OUT_DESTINATION_TYPEDEF dst;

	__LOGIC_OUTPUT_SETTINGS_TYPEDEF() : dst(), logic(__LOGIC_FUNCTION::__OR), ena(false){

	}

	void copy(const __LOGIC_OUTPUT_SETTINGS_TYPEDEF _other){
		copy(&_other);
	}

	void copy(const __LOGIC_OUTPUT_SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__LOGIC_OUTPUT_SETTINGS_TYPEDEF));
	}

	bool check(){
		if(!dst.check()) return false;
		if(logic >= __LOGIC_FUNCTION::__LAST) return false;

		return true;
	}

	void set_default(){
		__LOGIC_OUTPUT_SETTINGS_TYPEDEF();
	}
};

#pragma pack(push, 1)
template<uint8_t N_TIMERS, uint8_t N_LOG_INPUTS, uint8_t N_LOG_OUTPUTS>
class __SETTINGS_TYPEDEF{
public:
    __INPUTS_SETTINGS_TYPEDEF inputs[__SOURCE::__LAST];
    __LOGIC_INPUTS_SETTINGS_TYPEDEF log_inputs[N_LOG_INPUTS];
    __TIMERS_SETTINGS_TYPEDEF timers[N_TIMERS];
    __OUTPUT_SETTINGS_TYPEDEF outputs[__DESTINATION::__LAST];
    __LOGIC_OUTPUT_SETTINGS_TYPEDEF log_outputs[N_LOG_OUTPUTS];

    __SETTINGS_TYPEDEF(){

    }

    void copy(const __SETTINGS_TYPEDEF* const _other){
    	memcpy((void*)this, (void*)&_other, sizeof(__SETTINGS_TYPEDEF));
    }
    void copy(const __SETTINGS_TYPEDEF _other){
    	copy(&_other);
    }

    bool check(){
    	for(uint8_t i = 0; i < (sizeof(inputs) / sizeof(inputs[0])); i++){
    		if(!inputs[i].check()) return false;
    	}

    	for(uint8_t i = 0; i < (sizeof(log_inputs) / sizeof(log_inputs[0])); i++){
    		if(!log_inputs[i].check()) return false;
    	}

    	for(uint8_t i = 0; i < (sizeof(timers) / sizeof(timers[0])); i++){
    		if(!timers[i].check()) return false;
    	}

    	for(uint8_t i = 0; i < (sizeof(outputs) / sizeof(outputs[0])); i++){
    		if(!outputs[i].check()) return false;
    	}

    	for(uint8_t i = 0; i < (sizeof(log_outputs) / sizeof(log_outputs[0])); i++){
    		if(!log_outputs[i].check()) return false;
    	}

    	return false;
    }

    void set_default(){
    	for(uint8_t i = 0; i < (sizeof(inputs) / sizeof(inputs[0])); i++){
			inputs[i].set_default();
		}

		for(uint8_t i = 0; i < (sizeof(log_inputs) / sizeof(log_inputs[0])); i++){
			log_inputs[i].set_default();
		}

		for(uint8_t i = 0; i < (sizeof(timers) / sizeof(timers[0])); i++){
			timers[i].set_default();
		}

		for(uint8_t i = 0; i < (sizeof(outputs) / sizeof(outputs[0])); i++){
			outputs[i].set_default();
		}

		for(uint8_t i = 0; i < (sizeof(log_outputs) / sizeof(log_outputs[0])); i++){
			log_outputs[i].set_default();
		}
    }

};
#pragma pack(pop)

#pragma pack(push, 1)
template<uint8_t N_SELF_INPUTS, uint8_t N_SELF_OUTPUTS, uint8_t N_MODBUS_INPUTS, uint8_t N_MODBUS_OUTPUTS,
	uint8_t N_EXT_INPUTS, uint8_t N_EXT_OUTPUTS, uint8_t N_TIMERS, uint8_t N_LOG_INPUTS, uint8_t N_LOG_OUTPUTS>
class __IO_INFO_TYPEDEF{
public:
	const uint8_t self_inputs;
	const uint8_t mb_inputs;
	const uint8_t ext_inputs;
	const uint8_t log_inputs;
	const uint8_t timers;
	const uint8_t log_outputs;
	const uint8_t self_outputs;
	const uint8_t mb_outputs;
	const uint8_t ext_outputs;

	__IO_INFO_TYPEDEF() : self_inputs(N_SELF_INPUTS), mb_inputs(N_MODBUS_INPUTS), ext_inputs(N_EXT_INPUTS), log_inputs(N_LOG_INPUTS),
			self_outputs(N_SELF_OUTPUTS), mb_outputs(N_MODBUS_OUTPUTS), ext_outputs(N_EXT_OUTPUTS), log_outputs(N_LOG_OUTPUTS), timers(N_TIMERS){

	}
};
#pragma pack(pop)



}


#endif
