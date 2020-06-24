#ifndef _DEVICE_INFO_TYPES_H_
#define _DEVICE_INFO_TYPES_H_

#include "stdint.h"

namespace __ulp_device_info{

#pragma pack(push, 1)
typedef struct{
	uint16_t hw_ver;
	uint16_t report_size;
	char serial[15];
}__DEVICE_INFO_TYPEDEF;
#pragma pack(pop)

}

#endif
