#ifndef MESSAGE_H
#define MESSAGE_H

#include "stdint.h"
#include "string.h"
#include "module_base_types.h"

#include "cmd.h"

namespace _packet{

static const uint32_t packet_ctrl_bytes = 3;

class CPacket{
private:
    uint8_t* buff;
    uint8_t packet_size;
    uint16_t max_size;

    void inc_message_num(){
        buff[0] += 1;
    }

    void dec_message_num(){
        buff[0] -= 1;
    }

    void clr_message_num(){
        buff[0] = 0;
        packet_size = 1;
    }

public:
    CPacket(uint16_t _max_size) : max_size(_max_size), packet_size(1){
        buff = new uint8_t[_max_size];
        clr_message_num();
    }

    ~CPacket(){
        delete [] buff;
    }

    void init(){
        clr_message_num();
    }

    template<class CMD_T>
	bool add_message(__ulp_module::__TYPE::__TYPEDEF _module, CMD_T _command){
        if(max_size < (packet_size + packet_ctrl_bytes)) return false;
        buff[packet_size++] = packet_ctrl_bytes;
        buff[packet_size++] = (uint8_t)_module;
        buff[packet_size++] = (uint8_t)_command;
        inc_message_num();
        return true;
    }

    template<class CMD_T, class DATA_T>
	bool add_message(__ulp_module::__TYPE::__TYPEDEF _module, CMD_T _command, DATA_T* _data, uint32_t _data_size = sizeof(DATA_T)){
        if(max_size < (packet_size + _data_size + packet_ctrl_bytes)) return false;
        buff[packet_size++] = _data_size + packet_ctrl_bytes;
        buff[packet_size++] = (uint8_t)_module;
        buff[packet_size++] = (uint8_t)_command;

        memcpy(reinterpret_cast<void*>(&buff[packet_size]), reinterpret_cast<void*>(_data), _data_size);
        packet_size += _data_size;
        inc_message_num();
        return true;
    }

    template<class CMD_T, class DATA_T>
	bool add_message(__ulp_module::__TYPE::__TYPEDEF _module, CMD_T _command, DATA_T _data){
        return add_message(_module, _command, &_data);
    }

    bool add_message(__ulp_module::__TYPE::__TYPEDEF _module, _cmd::__CMD_TYPEDEF _command){
        return add_message(_module, _command.cmd, _command.ptr, _command.ndata_bytes);
    }

    bool parse_packet(__ulp_module::__TYPE::__TYPEDEF& _module, _cmd::__CMD_TYPEDEF& _command){
        if(buff[0] == 0) return false;

		_module = (__ulp_module::__TYPE::__TYPEDEF)buff[packet_size + 1];
        _command.cmd = buff[packet_size + 2];
        _command.ptr = &buff[packet_size + 3];
        _command.ndata_bytes = buff[packet_size] - packet_ctrl_bytes;
        packet_size += buff[packet_size];
        dec_message_num();
        return true;
    }

    uint8_t* get_ptr(){
        return buff;
    }

    uint8_t get_packet_size(){
        return packet_size;
    }

    void set_ptr(uint8_t* _ptr){
        buff = _ptr;
    }

};

}

#endif

