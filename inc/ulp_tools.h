#ifndef ULP_TOOLS_H
#define ULP_TOOLS_H

#pragma once

#include "ulp_lib.h"
#include "module_system_types.h"
#include "link_types.h"
#include <vector>


#if  _WIN64
 #if _DEBUG
 #pragma comment (lib, "../../x64/Debug/ulp_lib.lib")
 #else
 #pragma comment (lib, "../../x64/Release/ulp_lib.lib")
 #endif
#else 
 #if _DEBUG
 #pragma comment (lib, "../../Win32/Debug/ulp_lib.lib")
 #else
 #pragma comment (lib, "../../Win32/Release/ulp_lib.lib")
 #endif
#endif

using namespace std;
#define ATIME  10
#define ACK 0xF0
#define NACK 0x0F

static const char* module_type_strings[]  {

		"__SYSTEM ",
		"__SENSOR",
		"__RS485",
		"__HARD_IO",
		"__VIRTUAL_IO",
		"__FUNC_REMAP",
		"__POSITIONER",
		"__GMACHINE",
		"__TELEMETRY",
		"__ZONE_DETECTOR",
		"__LAST"

};

struct Command
{
	uint8_t module;
	uint8_t cmd;
	uint8_t* data_ptr;
	uint8_t ndata_bytes;
};

/*������� ���������� vector � ������� ��������� (��� ����������� �� USB) ��� ������� COM ������, ��� ����������� �� ����������������� �����
_ctype - ��� ����������� (USB ��� COM)
deviceList - ������ � ������� ���������
������������ �������� - true � ���������� ������, false � ��������� ������*/
bool  ulp_get_device_list(_ulp_link::__CONNECTION_TYPE_TYPEDEF _ctype, vector<wstring>& deviceList)
{
	deviceList.clear();
	uint32_t deviceNumber = ulp_get_num_of_connected_devices(_ctype);
	for (int i = 0; i < deviceNumber; i++)
	{
		wchar_t* deviceName = new wchar_t[200]; 
		if (ulp_get_name_of_device(_ctype, i, deviceName))
		{
			wstring wsname = wstring(deviceName);
			deviceList.push_back(wsname);
		}
		delete[] deviceName;
	}
	return !deviceList.empty(); 
}

/*������� �������� ������ �� ��������� ���������� � ������, ���������� ��������� � ���������� ����������� � ����������. 
�������� ������������ ������� ulp_create � ulp_link_connect.
_type - ��� ����������� (USB ��� COM)
_number - ����� ���������� USB ��� ����� COM-����� � �������, ������������ �������� ulp_get_device_list, ��� ���������� ����� COM-����
handle - ��������� �� ������� ������, ��� ���������� ��������� ����������. ������������ ��������.
_comSettings - ��������� ����� � ����� ����������. ������ ��� ����������� ����� COM ����.
������������ �������� - true � ���������� ������, false � ��������� ������*/
bool ulp_create_and_connect(_ulp_link::__CONNECTION_TYPE_TYPEDEF _type, uint8_t _number, void** handle,  _ulp_link::__COM_SETTINGS_TYPEDEF* _comSettings= NULL)
{
	*handle = ulp_create(_type);
	if (!*handle) return false;

	if (!ulp_link_connect(*handle, _number)) return false;

	if ((_type == _ulp_link::__TYPE_COM) && _comSettings)
	{
		if (ulp_change_link_settings(*handle, _comSettings)) return false;
	}
	
	return true;

}
/*������� ��������� ���������� � ����������� � ����������� ������, ������� � ������ ��� ����. 
�������� ������������ ������� ulp_link_disconnect � ulp_free  */
bool ulp_disconnect_and_free(void* handle)
{
	if (!ulp_link_disconnect(handle)) return false;
	ulp_free(handle);
	return true;
}

//���������, ������� ������ ������ � ��������� �������, ���������� �� ����������.
Command lastCommand;

//���������� ������ � ������
int inBuff_num = 0;

// ��������� ��� �������� ������ �� ������
vector<__ulp_m_sensor::__SENS_DATA_TYPEDEF> buff_data;

//������� ��������� ������. ��������� ���������� ��������� lastCommand �������, ����������� �� ��������� �� ����������
void callback_handler(__ulp_module::__TYPE::__TYPEDEF& _module, uint8_t _cmd, uint8_t* _ptr, uint8_t ndata_bytes)
{
	// ��������� ��������� 
	lastCommand.cmd = _cmd;
	lastCommand.module = _module;
	lastCommand.data_ptr = _ptr;
	lastCommand.ndata_bytes = ndata_bytes;

	// ���� ������ �� ������, �� �������� �� � vector buff_data
	if ((lastCommand.module == __ulp_module::__TYPE::__SYSTEM) && (lastCommand.cmd == __ulp_m_system::__CMD::__GET_LOG_DATA))
	{
		__ulp_m_system::__SEND_LOG_DATA_TYPEDEF* pSend_log_data = (__ulp_m_system::__SEND_LOG_DATA_TYPEDEF*)_ptr;

		//���������� ������� ������ � ������ �� ������ �������
		inBuff_num = pSend_log_data->status.queue;
		
		//���������� ������� ������ � �������
		uint8_t num_datas = (ndata_bytes - 2) / 10;

		for (int i = 0; i < num_datas; i++)
		{
			buff_data.push_back(pSend_log_data->data[i]);
		}
		
	}

}

// ������� ������� ���������� � lastCommand
void ulp_clear_last_command()
{
	lastCommand.cmd = 0;
	lastCommand.data_ptr = 0;
	lastCommand.module = 0;
	lastCommand.ndata_bytes = 0;
}

bool ulp_clear_send_exchange(void* ulp_device, uint8_t _module, uint8_t _command, uint8_t* _data, uint32_t _data_size, bool isReadBeforeWrite = false, uint32_t sleep_time = ATIME )
{
	ulp_clear_last_command();
	ulp_send_message(ulp_device, _module, _command, _data, _data_size);
	ulp_exchange(ulp_device, sleep_time, isReadBeforeWrite);
	return lastCommand.ndata_bytes;

}

#endif
