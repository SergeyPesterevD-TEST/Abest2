#ifndef _MODULE_RS485_TYPES_H_
#define _MODULE_RS485_TYPES_H_

#include "stdint.h"
#include "module_base_types.h"
#include "string.h"

namespace __ulp_m_rs485{

class __MODE{
public:
	typedef enum{
		__MODBUS,
		__SPPU,
		__LAST
	}__TYPEDEF;
};

class __CMD{
public:
	typedef enum{
		__LAST = __ulp_module::__SHARED_CMD::__PRIVATE_CMD_START,
		__SUB_MODULE_CMD_START = 60
	}__TYPEDEF;
};

}

#endif
