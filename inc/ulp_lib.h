#ifndef ULP_LIB_H
#define ULP_LIB_H
#define WINVER 0x0501

#include <stdint.h>
#include <windows.h>
#include "link_types.h"
#include "module_base_types.h"


#define LIR_ULP_API  extern "C" __declspec(dllexport)

/* Функция возвращает количество подключенных устройств при подключении по USB и колчество COM-портов компьютера при подключении через COM-порт
 _ulp_link - тип подключения (USB или COM)*/
LIR_ULP_API uint32_t  ulp_get_num_of_connected_devices(_ulp_link::__CONNECTION_TYPE_TYPEDEF type);

 /*Функция возвращает имя устройства при подключении по USB и название COM порта при подключении через COM.
_ulp_link - тип подключения (USB или COM)
 device_Number - порядковый номер устройства (от 0 до ulp_get_num_of_connected_devices) в системе.
 device_Name - указатель на строку. Не должен быть NULL.
 Возвращаемое значение - true, если устройство с номером device_Number существует, false в противном случае*/
LIR_ULP_API bool ulp_get_name_of_device(_ulp_link::__CONNECTION_TYPE_TYPEDEF, uint8_t device_Number, wchar_t * device_Name);

/*Функция создает в памяти и возвращает указатель на устройство, подключенное по _ulp_link
_ulp_link - тип подключения (USB или COM)*/
LIR_ULP_API void* ulp_create(_ulp_link::__CONNECTION_TYPE_TYPEDEF  connection_type);

/*Функция освобождает память, занятую устройством.
 ulp_device - указатель на устройтсво, полученный с помощью ulp_create*/
LIR_ULP_API void  ulp_free(void *ulp_device);


/*Функция создает соединение с физическим устройством 
 ulp_device - указатель на устройство, полученный с помощью ulp_create
 device_Number - порядковый номер устройства (от 0 до ulp_get_num_of_connected_devices) в системе.
 Возвращаемое значение - true в результате успеха, false в противном случае*/
LIR_ULP_API bool ulp_link_connect(void* ulp_device, uint8_t device_Number);

/*Функция разрывает соединение с физическим устройством
 ulp_device - указатель на устройство, полученный с помощью ulp_create
 Возвращаемое значение - true в результате успеха, false в противном случае*/
LIR_ULP_API bool ulp_link_disconnect(void* ulp_device);

 /*Функция производит настройки COM порта и номер устройства. Испольлзуется только при подключении устройства через COM порт. 
 Должна вызываться только после ulp_link_connect.
 ulp_device - указатель на устройство, полученный с помощью ulp_create
 settings - настройки порта и номер устройства.
 Возвращаемое значение - true в результате успеха, false в противном случае*/
LIR_ULP_API bool ulp_change_link_settings(const void* ulp_device, _ulp_link::__COM_SETTINGS_TYPEDEF* settings);

/* Функция создает сообщение для устройства и записывает его в посылку для устройства. Размер посылки для устройства ограничен. 
 Для подключения по USB - 254 байта, для COM- 251 байт. Следует отметить, что сообщение только помещается в ближайшую посылку. Отправка
 сообщения физическому устройству не происходит.
 ulp_device - указатель на устройство, полученный с помощью ulp_create
 _module - номер модуля, которому предназначается сообщение.
 _command - номер команды для модуля _module
 _data - указатель на данные для передачи в устройство
 _data_size - размер данных в байтах
 Возвращаемое значение - true, если сообщение помещается в ближайшую посылку,  false в противном случае*/
LIR_ULP_API bool ulp_send_message(void* ulp_device, uint8_t _module, uint8_t _command, uint8_t* _data, uint32_t _data_size);



 /*Функция запускает обмен посылками между устройством и компьютером.
 ulp_device - указатель на устройство, полученный с помощью ulp_create
 SleepTime - время в миллисекундах между отправкой послыки устройству и чтением посылки, полученной от устройства.
 ReadBeforeWrite - устанавливает порядок, в котором будет производится чтение и запись посылки. 
 Если ReadBeforeWrite = true, то сначала производится получение посылки, полученной от устройства, затем выполняется задержка ReadBeforeWrite, затем выполняется запись посылки в устройство
 Если ReadBeforeWrite = false, то сначала производится запись посылки в устройство, затем выполняется задержка ReadBeforeWrite, затем выполняется получение посылки от устройства*/
LIR_ULP_API void ulp_exchange(void* ulp_device, uint32_t SleepTime = 0, bool ReadBeforeWrite = true);

/* Процедура задает функцию обратного вызыва для устройства. Данная функция будет вызвана для каждого сообщения из посылки, полученной от устройства
в процессе работы функции ulp_exchange.
ulp_device - указатель на устройство, полученный с помощью ulp_create
_callback - указатель на функцию, которая будет вызвана для каждого сообщения из посылки, полученной от устройства
в процессе работы функции ulp_exchange.*/
LIR_ULP_API void ulp_set_message_callback(const void* ulp_device, void(*_callback)(__ulp_module::__TYPE::__TYPEDEF& _module, uint8_t _cmd, uint8_t* _ptr, uint8_t ndata_bytes));
#endif