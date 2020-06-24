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

/*Функция возвращает vector с именами устройств (при подключении по USB) или именами COM портов, при подключении по последовательному порту
_ctype - тип подключения (USB или COM)
deviceList - массив с именами устройств
Возвращаемое значение - true в результате успеха, false в противном случае*/
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

/*Функция выделяет память на структуру устройства в памяти, возвращает указатель и производит подключение к устройству. 
Является объединением функций ulp_create и ulp_link_connect.
_type - тип подключения (USB или COM)
_number - номер устройства USB или номер COM-порта в массиве, возвращаемом функцией ulp_get_device_list, при поключении через COM-порт
handle - указатель на область памяти, где расположен указатель устройства. Возвращаемое значение.
_comSettings - настройки порта и номер устройства. Только для подключения через COM порт.
Возвращаемое значение - true в результате успеха, false в противном случае*/
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
/*Функция разрывает соединение с устройством и освобождает память, занятую в памяти под него. 
Является объединением функций ulp_link_disconnect и ulp_free  */
bool ulp_disconnect_and_free(void* handle)
{
	if (!ulp_link_disconnect(handle)) return false;
	ulp_free(handle);
	return true;
}

//Структура, которая хранит данные о последней команде, полученной от устройства.
Command lastCommand;

//Количество данных в буфере
int inBuff_num = 0;

// Контейнер для хранения данных из буфера
vector<__ulp_m_sensor::__SENS_DATA_TYPEDEF> buff_data;

//Функция обратного вызова. Заполняет глобальную структуру lastCommand данными, полученными из сообщения от устройства
void callback_handler(__ulp_module::__TYPE::__TYPEDEF& _module, uint8_t _cmd, uint8_t* _ptr, uint8_t ndata_bytes)
{
	// Заполняем структуру 
	lastCommand.cmd = _cmd;
	lastCommand.module = _module;
	lastCommand.data_ptr = _ptr;
	lastCommand.ndata_bytes = ndata_bytes;

	// Если данные из буфера, то помещаем их в vector buff_data
	if ((lastCommand.module == __ulp_module::__TYPE::__SYSTEM) && (lastCommand.cmd == __ulp_m_system::__CMD::__GET_LOG_DATA))
	{
		__ulp_m_system::__SEND_LOG_DATA_TYPEDEF* pSend_log_data = (__ulp_m_system::__SEND_LOG_DATA_TYPEDEF*)_ptr;

		//Определяем сколько данных в буфере на момент запроса
		inBuff_num = pSend_log_data->status.queue;
		
		//Определяем сколько данных в команде
		uint8_t num_datas = (ndata_bytes - 2) / 10;

		for (int i = 0; i < num_datas; i++)
		{
			buff_data.push_back(pSend_log_data->data[i]);
		}
		
	}

}

// Функция очищает информацию в lastCommand
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
