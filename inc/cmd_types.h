#ifndef _CMD_TYPES_H_
#define _CMD_TYPES_H_

namespace __ulp_cmd{

class __RESULT{
public:
	typedef enum{
		__ACK = 0xF0,
		__NACK = 0x0F
	}__TYPEDEF;
};

}

#endif
