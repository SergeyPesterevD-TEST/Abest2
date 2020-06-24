#ifndef _MODULE_BASE_TYPES_H_
#define _MODULE_BASE_TYPES_H_

namespace __ulp_module{

class __STATE{
public:
	typedef enum{
		__ENABLE = 0,
		__DISABLE,
		__LAST
	}__TYPEDEF;
};

class __TYPE{
public:
	typedef enum{
		__SYSTEM = 0,
		__SENSOR,
		__RS485,
		__HARD_IO,
		__VIRTUAL_IO,
		__FUNC_REMAP,
		__POSITIONER,
		__GMACHINE,
		__TELEMETRY,
		__ZONE_DETECTOR,
		__LAST
	}__TYPEDEF;
};

class __SHARED_CMD{
public:
	typedef enum{
		__GET_MODULE_INFO = 0,
		__GET_SUB_MODULE_NUM,
		__GET_SUB_MODULE_INFO,
		__GET_MODULE_STATE,
		__SET_MODULE_STATE,
		__GET_MODULE_MODE,
		__SET_MODULE_MODE,
		__GET_MODULE_SETTINGS,
		__SET_MODULE_SETTINGS,
		__GET_SUB_MODULE_SETTINGS,
		__SET_SUB_MODULE_SETTINGS,
		__SAVE_MODULE_SETTINGS,
		__LOAD_MODULE_SETTINGS,
		__LAST,
		__PRIVATE_CMD_START = 20
	}__TYPEDEF;
};

}

#endif
