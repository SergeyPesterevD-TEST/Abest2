#ifndef _SUB_MODULE_RS485_SPPU_TYPES_H_
#define _SUB_MODULE_RS485_SPPU_TYPES_H_

#include "module_rs485_types.h"
#include "module_sensor_types.h"
#include "module_positioner_types.h"

namespace __ulp_sm_rs485_sppu{

static const uint8_t __LIR_BASE_ADDR = 100;

class __STATE{
public:
	typedef enum{
		__EXT_IO_TRANSMIT = 0,
		__EXT_IO_RECEIVE,
		__LIR_SYNC_TRANSMIT,
		__LIR_SYNC_RECEIVE,
		__LIR_WAIT_INTERPOLATION,
		__LIR_SEND_SYNCHRO,
		__IDLE,
		__LAST
	}__TYPEDEF;
};

class __MODE{
public:
	typedef enum{
		__MASTER = 0,
		__SLAVE,
		__LAST
	}__TYPEDEF;
};

class __TRANSACTION_STATUS{
public:
	typedef enum{
		__WAITING_EXCHANGE = 0,
		__EXCHANGING,
		__EXCHANGE_COMPLETE,
		__EXCHANGE_ERROR,
		__LAST
	}__TYPEDEF;
};

#pragma pack(push, 1)
class __LIR_SYNC_ANSWER_TYPEDEF{
public:
	uint8_t addr;
	uint8_t cmd;
	__ulp_m_sensor::__SENS_DATA_TYPEDEF sens;
	uint32_t ext_otputs;
	uint8_t self_inputs;
	uint16_t crc;
};
#pragma pack(pop)

#pragma pack(push, 1)
class __LIR_SYNC_REQUEST_TYPEDEF{
public:
	uint8_t addr;
	uint8_t cmd;
	uint32_t ext_inputs;
	uint32_t self_outputs;
};
#pragma pack(pop)

#pragma pack(push, 1)
class __LIR_SYNC_SYNCHRO_REQUEST_TYPEDEF{
public:
	uint8_t addr;
	uint8_t cmd;
	uint16_t crc;
};
#pragma pack(pop)

#pragma pack(push, 1)
class __LIR_REQUEST_COORDINATE_TYPEDEF{
public:
	uint8_t axis;
	uint64_t coordinate;

	__LIR_REQUEST_COORDINATE_TYPEDEF(uint8_t _axis, uint64_t _coord) : axis(_axis){
		memcpy((void*)&this->coordinate, (void*)&_coord, sizeof(coordinate));
	}

	__LIR_REQUEST_COORDINATE_TYPEDEF(){
		memset((void*)this, 0, sizeof(__LIR_REQUEST_COORDINATE_TYPEDEF));
	}
};
#pragma pack(pop)

#pragma pack(push, 1)
class __LIR_986_SYNCDATA_TYPEDEF{
public:
	uint8_t addr;
	uint8_t cmd;
	uint8_t byte_num;
	uint32_t io;
	uint16_t crc;
};
#pragma pack(pop)

class __POS_CMD_DATA_TYPEDEF{
public:
	bool is_cmd;
	uint64_t coordinate;
};

class __INTERLIR_CMD{
public:
	typedef enum{
		__SYNC = 0,
		__REF_SEARCH,
		__MOVE_TO,
		__MOVE_TO_W_SPEED,
		__STOP,
		__SET_G_OFFSET,
		__CHANGE_G_SYS,
		__LAST
	}__TYPEDEF;
};

#pragma pack(push, 1)
template<uint32_t MAX_SYNC_AXIS>
class __SETTINGS_TYPEDEF{
public:
	__MODE::__TYPEDEF mode;
	uint8_t axis;
	bool ext_io_ena;
	uint8_t ext_io_addr;
	uint8_t max_series_errors;
	bool sens_upd;

	__SETTINGS_TYPEDEF() : mode(__MODE::__SLAVE), axis(0), ext_io_ena(false),
			ext_io_addr(1), max_series_errors(20), sens_upd(false){

	}

	void copy(const __SETTINGS_TYPEDEF* const _other){
		memcpy((void*)this, (void*)_other, sizeof(__SETTINGS_TYPEDEF));
	}

	void copy(const __SETTINGS_TYPEDEF _other){
		copy(&_other);
	}

	bool check(){
		if(mode >= __MODE::__LAST) return false;
		if(axis >= MAX_SYNC_AXIS) return false;

		return true;
	}

	void set_default(){
		__SETTINGS_TYPEDEF();
	}
};
#pragma pack(pop)

class __AXIS_DATA_TYPEDEF{
public:
	__ulp_m_sensor::__SENS_DATA_TYPEDEF sens_data;
	__ulp_m_positioner::__RESULT::__TYPEDEF pos_result;
	uint8_t self_inp;
	uint32_t ext_outputs;
	uint16_t errors;

	__AXIS_DATA_TYPEDEF() : sens_data(), pos_result(__ulp_m_positioner::__RESULT::__DONE),
									self_inp(0), ext_outputs(0), errors(0){

	}

	void set_default(){
		__AXIS_DATA_TYPEDEF();
	}
};







}



#endif
