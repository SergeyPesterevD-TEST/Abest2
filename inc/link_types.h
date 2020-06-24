#ifndef LINKs_TYPES_H
#define LINKs_TYPES_H

namespace _ulp_link {

typedef enum{
    __STATE_CONNECTED = 0,
    __STATE_DISCONNECTED,
    __STATE_LAST
}__CONNECTION_STATE_TYPEDEF;

typedef enum{
	__TYPE_USB = 0,
	__TYPE_COM,
	__TYPE_LAST
}__CONNECTION_TYPE_TYPEDEF;

typedef enum{
	__PARITY_NO = 0,
	__PARITY_EVEN = 2,
	__PARITY_ODD = 3
}__COM_PARITY_TYPEDEF;

typedef enum{
	__STOP_BITS_1 = 1,
	__STOP_BITS_1_5 = 3,
	__STOP_BITS_2 = 2
}__COM_STOP_B_TYPEDEF;

typedef struct{
	uint8_t dev_addr;
	uint32_t baudrate;
	__COM_PARITY_TYPEDEF parity;
	__COM_STOP_B_TYPEDEF nstop;
}__COM_SETTINGS_TYPEDEF;




}

#endif

