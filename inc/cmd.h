#ifndef CMD_H
#define CMD_H

#include "stdint.h"

namespace _cmd {

typedef class __CMD_TYPEDEF{
public:
    uint8_t cmd;
    uint8_t ndata_bytes;
    uint8_t* ptr;

    __CMD_TYPEDEF() : cmd(0), ptr(0), ndata_bytes(0){

    }

    template<class CMD_T, class DATA_T>
    __CMD_TYPEDEF(CMD_T _cmd, DATA_T* _data, uint16_t _data_size = sizeof(DATA_T)) :
                                        ndata_bytes(_data_size){
        cmd = reinterpret_cast<uint8_t>(_cmd);
        ptr = reinterpret_cast<uint8_t*>(&_data);
    }

    template<class CMD_T>
    __CMD_TYPEDEF(CMD_T _cmd) : ndata_bytes(0), ptr(0){
        cmd = reinterpret_cast<uint8_t>(_cmd);
    }
}__CMD_TYPEDEF;

}

#endif

