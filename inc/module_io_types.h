#ifndef _MODULE_IO_TYPES_H_
#define _MODULE_IO_TYPES_H_

#include "module_base_types.h"

namespace __ulp_m_io{

class __CMD{
public:
	typedef enum{
		__SET_OUTPUTS = __ulp_module::__SHARED_CMD::__PRIVATE_CMD_START,
		__GET_OUTPUTS,
		__GET_INPUTS,
		__SET_SINGLE_OUTPUT,
		__LAST
	}__TYPEDEF;
};


}



#endif
