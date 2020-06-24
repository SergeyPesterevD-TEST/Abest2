#ifndef ULP_LIB_H
#define ULP_LIB_H
#define WINVER 0x0501

#include <stdint.h>
#include <windows.h>
#include "link_types.h"
#include "module_base_types.h"


#define LIR_ULP_API  extern "C" __declspec(dllexport)

/* ������� ���������� ���������� ������������ ��������� ��� ����������� �� USB � ��������� COM-������ ���������� ��� ����������� ����� COM-����
 _ulp_link - ��� ����������� (USB ��� COM)*/
LIR_ULP_API uint32_t  ulp_get_num_of_connected_devices(_ulp_link::__CONNECTION_TYPE_TYPEDEF type);

 /*������� ���������� ��� ���������� ��� ����������� �� USB � �������� COM ����� ��� ����������� ����� COM.
_ulp_link - ��� ����������� (USB ��� COM)
 device_Number - ���������� ����� ���������� (�� 0 �� ulp_get_num_of_connected_devices) � �������.
 device_Name - ��������� �� ������. �� ������ ���� NULL.
 ������������ �������� - true, ���� ���������� � ������� device_Number ����������, false � ��������� ������*/
LIR_ULP_API bool ulp_get_name_of_device(_ulp_link::__CONNECTION_TYPE_TYPEDEF, uint8_t device_Number, wchar_t * device_Name);

/*������� ������� � ������ � ���������� ��������� �� ����������, ������������ �� _ulp_link
_ulp_link - ��� ����������� (USB ��� COM)*/
LIR_ULP_API void* ulp_create(_ulp_link::__CONNECTION_TYPE_TYPEDEF  connection_type);

/*������� ����������� ������, ������� �����������.
 ulp_device - ��������� �� ����������, ���������� � ������� ulp_create*/
LIR_ULP_API void  ulp_free(void *ulp_device);


/*������� ������� ���������� � ���������� ����������� 
 ulp_device - ��������� �� ����������, ���������� � ������� ulp_create
 device_Number - ���������� ����� ���������� (�� 0 �� ulp_get_num_of_connected_devices) � �������.
 ������������ �������� - true � ���������� ������, false � ��������� ������*/
LIR_ULP_API bool ulp_link_connect(void* ulp_device, uint8_t device_Number);

/*������� ��������� ���������� � ���������� �����������
 ulp_device - ��������� �� ����������, ���������� � ������� ulp_create
 ������������ �������� - true � ���������� ������, false � ��������� ������*/
LIR_ULP_API bool ulp_link_disconnect(void* ulp_device);

 /*������� ���������� ��������� COM ����� � ����� ����������. ������������� ������ ��� ����������� ���������� ����� COM ����. 
 ������ ���������� ������ ����� ulp_link_connect.
 ulp_device - ��������� �� ����������, ���������� � ������� ulp_create
 settings - ��������� ����� � ����� ����������.
 ������������ �������� - true � ���������� ������, false � ��������� ������*/
LIR_ULP_API bool ulp_change_link_settings(const void* ulp_device, _ulp_link::__COM_SETTINGS_TYPEDEF* settings);

/* ������� ������� ��������� ��� ���������� � ���������� ��� � ������� ��� ����������. ������ ������� ��� ���������� ���������. 
 ��� ����������� �� USB - 254 �����, ��� COM- 251 ����. ������� ��������, ��� ��������� ������ ���������� � ��������� �������. ��������
 ��������� ����������� ���������� �� ����������.
 ulp_device - ��������� �� ����������, ���������� � ������� ulp_create
 _module - ����� ������, �������� ��������������� ���������.
 _command - ����� ������� ��� ������ _module
 _data - ��������� �� ������ ��� �������� � ����������
 _data_size - ������ ������ � ������
 ������������ �������� - true, ���� ��������� ���������� � ��������� �������,  false � ��������� ������*/
LIR_ULP_API bool ulp_send_message(void* ulp_device, uint8_t _module, uint8_t _command, uint8_t* _data, uint32_t _data_size);



 /*������� ��������� ����� ��������� ����� ����������� � �����������.
 ulp_device - ��������� �� ����������, ���������� � ������� ulp_create
 SleepTime - ����� � ������������� ����� ��������� ������� ���������� � ������� �������, ���������� �� ����������.
 ReadBeforeWrite - ������������� �������, � ������� ����� ������������ ������ � ������ �������. 
 ���� ReadBeforeWrite = true, �� ������� ������������ ��������� �������, ���������� �� ����������, ����� ����������� �������� ReadBeforeWrite, ����� ����������� ������ ������� � ����������
 ���� ReadBeforeWrite = false, �� ������� ������������ ������ ������� � ����������, ����� ����������� �������� ReadBeforeWrite, ����� ����������� ��������� ������� �� ����������*/
LIR_ULP_API void ulp_exchange(void* ulp_device, uint32_t SleepTime = 0, bool ReadBeforeWrite = true);

/* ��������� ������ ������� ��������� ������ ��� ����������. ������ ������� ����� ������� ��� ������� ��������� �� �������, ���������� �� ����������
� �������� ������ ������� ulp_exchange.
ulp_device - ��������� �� ����������, ���������� � ������� ulp_create
_callback - ��������� �� �������, ������� ����� ������� ��� ������� ��������� �� �������, ���������� �� ����������
� �������� ������ ������� ulp_exchange.*/
LIR_ULP_API void ulp_set_message_callback(const void* ulp_device, void(*_callback)(__ulp_module::__TYPE::__TYPEDEF& _module, uint8_t _cmd, uint8_t* _ptr, uint8_t ndata_bytes));
#endif