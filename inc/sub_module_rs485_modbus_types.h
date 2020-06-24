#ifndef _SUB_MODULE_RS485_MODBUS_TYPES_H_
#define _SUB_MODULE_RS485_MODBUS_TYPES_H_

#include "module_rs485_types.h"

namespace __ulp_sm_rs485_modbus{

class __CMD{
public:
	typedef enum{
		__GET_ERROR_CNTR = __ulp_m_rs485::__CMD::__SUB_MODULE_CMD_START,
		__CLR_ERROR_CNTR,
		__GET_LAST_ERROR,
		__SEND_REQUEST,
		__GET_ANSWER,
		__LAST
	}__TYPEDEF;
};

class __MODE{
public:
	typedef enum{
		__SLAVE = 0,
		__MASTER,
		__LAST
	}__TYPEDEF;
};

class __ERROR{
public:
	typedef enum{
		__BAD_FUNCTION = 1,
		__BAD_ADDRESS,
		__BAD_DATA,
		__EPIC_FAIL,
		__SLOW_WORKING_SLAVE,
		__BUSY_SLAVE,
		__BAD_PROGRAM_REQUEST,
		__BROKEN_SLAVE,
		__ANSWER_TIMEOUT,
		__CRC_MISMATCH,
		__NO_ERROR,
		__LINE_MALFUNCTION,
		__LAST
	}__TYPEDEF;
};

class __STATE{
public:
	typedef enum{
		__IDLE,
		__RECEIVE,
		__TRANSMIT,
		__WORKING,
		__LAST
	}__TYPEDEF;
};

class __FUNCTIONS{
public:
	typedef enum{
		__READ_COIL_STATUS = 0x01,
		__READ_DISCRETE_INPUTS,
		__READ_HOLDING_REGISTERS,
		__READ_INPUT_REGISTERS,
		__WRITE_SINGLE_COIL,
		__WRITE_SINGLE_REGISTER,
		__WRITE_MULTIPLE_COILS = 0x0F,
		__WRITE_MULTIPLE_REGISTERS,
		__REPORT_SLAVE_ID = 0x11,
		__ENCAPSULATED_INTERFACE_TRANSPORT = 0x2B
	}__TYPEDEF;
};

class __PARITY{
public:
	typedef enum{
		__EVEN = 0,
		__ODD,
		__SPACE,
		__MARK,
		__NO,
		__LAST
	}__TYPEDEF;
};

class __STOP_BITS{
public:
	typedef enum{
		__1 = 0,
		__1_5,
		__2,
		__LAST
	}__TYPEDEF;
};

#pragma pack(push, 1)
class __SETTINGS_TYPEDEF{
public:
	__MODE::__TYPEDEF mode;
	uint8_t address;
	uint16_t timeout;
	uint32_t baudrate;
	__PARITY::__TYPEDEF parity_type;
	__STOP_BITS::__TYPEDEF nstop_bits;

	__SETTINGS_TYPEDEF() : mode(__MODE::__SLAVE), address(247), timeout(100), baudrate(115200),
			parity_type(__PARITY::__NO), nstop_bits(__STOP_BITS::__1){

	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}

	void copy(const __SETTINGS_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if(mode >= __MODE::__LAST) return false;
		if(parity_type >= __PARITY::__LAST) return false;
		if(nstop_bits >= __STOP_BITS::__LAST) return false;
		if((address == 0) | (address > 247)) return false;

		return true;
	}

	void set_default(){
		__SETTINGS_TYPEDEF();
	}
};
#pragma pack(pop)


template<class Data_TYPE>
class Cmodbus_data_interface{
private:
	uint16_t regnum;
	uint16_t start_addr;
public:
	Cmodbus_data_interface(uint16_t _start_addr, uint16_t _regnum) :
			regnum(_regnum), start_addr(_start_addr){
	}

	virtual ~Cmodbus_data_interface(){

	}

	uint16_t get_start_addr(){
		return start_addr;
	}

	uint16_t get_reg_num(){
		return regnum;
	}

	virtual void write_reg(uint16_t _addr, Data_TYPE _value){}

	virtual Data_TYPE read_reg(uint16_t _addr){
		return (Data_TYPE)0;
	}

	uint16_t get_end_addr(void){
		return start_addr + regnum;
	}
};

class Cmodbus_EIT_interface{
private:

public:
	Cmodbus_EIT_interface(){

	}

	virtual ~Cmodbus_EIT_interface(){

	}

	virtual uint8_t call(uint8_t* ptr){
		return false;
	}
};



}



#endif
