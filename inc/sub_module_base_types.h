#ifndef _SUB_MODULE_BASE_TYPES_H_
#define _SUB_MODULE_BASE_TYPES_H_

#include "stdint.h"

#pragma pack(push, 1)
class __INFO_TYPEDEF{
private:
	__INFO_TYPEDEF() : type(0), version(0){

	}
public:
	const uint8_t type;
	const uint8_t version;

	__INFO_TYPEDEF(const uint8_t& _type, const uint8_t& _ver) : type(_type), version(_ver){

	}
};
#pragma pack(pop)

#endif
