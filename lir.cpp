#include "lir.h"

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

//Структура, которая хранит данные о последней команде, полученной от устройства.
Command lastCommand;
//Количество данных в буфере
int inBuff_num = 0;
// Контейнер для хранения данных из буфера
QVector<__ulp_m_sensor::__SENS_DATA_TYPEDEF> buff_data;

/*Функция разрывает соединение с устройством и освобождает память, занятую в памяти под него.
Является объединением функций ulp_link_disconnect и ulp_free  */
bool ulp_disconnect_and_free(void* handle)
{
    if (!ulp_link_disconnect(handle)) return false;
    ulp_free(handle);
    return true;
}

// Функция очищает информацию в lastCommand
void ulp_clear_last_command()
{
    lastCommand.cmd = 0;
    lastCommand.data_ptr = 0;
    lastCommand.module = 0;
    lastCommand.ndata_bytes = 0;
}


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


Lir::Lir(QObject *parent) : QObject(parent)
{

}

int Lir::LirMain()
{
    _ulp_link::__CONNECTION_TYPE_TYPEDEF ctype = _ulp_link::__TYPE_USB;
    int DeviceCount=ulp_get_num_of_connected_devices(ctype);
    qDebug() << "LIR Найдено " << DeviceCount;

    wchar_t device_Name;

    for (int i=0;i<<DeviceCount;i++)
    {
        ulp_get_name_of_device(ctype,i,&device_Name);
        qDebug() << "LIR Найдено " << i << device_Name;
    }

    if (DeviceCount<=0) { return -1; } //если не нашли ЛИР

    void* handle = NULL;

    handle = ulp_create(ctype);

    if (ulp_link_connect(&handle, 1))  // работаем с устройством 0 )
    {
        qDebug() << "LIR Создание и подключение:OK !";
    }
    else
    {
        qDebug() << "LIR Ошибка подключения!";
        return 1;
    }

    // Устанавливаем функцию обратного вызыва для приема сообщений от устройства
    ulp_set_message_callback(handle, callback_handler);

    // Проверяем, что модуль 1 - это модуль датчика

    uint8_t sensor_module_num = 1;
    ulp_send_message(handle, sensor_module_num, __ulp_module::__SHARED_CMD::__GET_MODULE_INFO, NULL, 0);
    ulp_exchange(handle, ATIME, false);
    if (lastCommand.ndata_bytes)
    {
        __ulp_module::__TYPE::__TYPEDEF module_type = (__ulp_module::__TYPE::__TYPEDEF)lastCommand.data_ptr[0];
        if (module_type == __ulp_module::__TYPE::__SENSOR) qDebug() << "Тип модуля "<<(int)sensor_module_num<<": Датчик"<<endl;

    }

    // Очищаем структуру
    ulp_clear_last_command();

    //Проверяем включен ли модуль датчика и, если не включен, включаем
    ulp_send_message(handle, sensor_module_num, __ulp_module::__SHARED_CMD::__GET_MODULE_STATE, NULL, 0);
    ulp_exchange(handle, ATIME, false);
    uint8_t isModuleDisable;
    if (lastCommand.ndata_bytes)
    {
        isModuleDisable = lastCommand.data_ptr[0]; // 0 -включен, 1- выключен
        if (isModuleDisable)
        {
            ulp_clear_last_command();
            // Включаем модуль датчика
            uint8_t data = 0;
            ulp_send_message(handle, sensor_module_num, __ulp_module::__SHARED_CMD::__SET_MODULE_STATE, &data, sizeof(data));
            ulp_exchange(handle, ATIME, false);
            if (lastCommand.ndata_bytes && (lastCommand.data_ptr[0] == ACK))
            {
                isModuleDisable = 0;
            }

        }
        if (!isModuleDisable) qDebug() << "Модуль датчика включен !" << endl;
        else
        {
            qDebug() << "Модуль датчика выключен !" << endl;

        }

    }

    // Устанавливаем режим работы модуля датчика "Инкрементный".

    // Выбираем подмодуль инкрементных датчиков
    uint8_t submodule = __ulp_m_sensor::__SUB_MODULE_TYPES::__INCREMENTAL;
    ulp_clear_last_command();
    ulp_send_message(handle, sensor_module_num, __ulp_module::__SHARED_CMD::__SET_MODULE_MODE, &submodule, sizeof(submodule));
    ulp_exchange(handle, ATIME, false);
    if (lastCommand.ndata_bytes && (lastCommand.data_ptr[0] == ACK))
        qDebug() << "Режим работы модуля: Инкрементный"<<endl;


    for (int i = 0; i < 10; i++)
    {

        // Обновляем и запрашиваем текущую координату датчика

        ulp_clear_last_command();
        ulp_send_message(handle, sensor_module_num, __ulp_m_sensor::__CMD::__UPD_SENSOR_DATA, 0, 0);
        uint8_t axis = 0;
        ulp_send_message(handle, sensor_module_num, __ulp_m_sensor::__CMD::__GET_SENSOR_DATA, &axis, sizeof(axis));
        ulp_exchange(handle, ATIME, false);

        if (lastCommand.ndata_bytes)
        {
            __ulp_m_sensor::__SENS_DATA_TYPEDEF* psensor_data = (__ulp_m_sensor::__SENS_DATA_TYPEDEF*)lastCommand.data_ptr;
            __ulp_m_sensor::__SENS_DATA_TYPEDEF sensor_data(psensor_data);
            qDebug() << "Текущая координата:" << sensor_data.coordinate << endl;
            qDebug() << "Биты ошибок:" << sensor_data.status.alarm_bits << endl;
            qDebug() << "Ошибка коррекции:" << sensor_data.status.correction_error << endl;
            qDebug() << "Не захвачена референтная метка:" << sensor_data.status.no_ref << endl;
            qDebug() << "Референтна метка захвачена:" << sensor_data.status.ref_capture << endl;
            qDebug() << "Ошибка датчика:" << sensor_data.status.sensor_error << endl << endl;


        }

        Sleep(1000);
    }

    ulp_disconnect_and_free(handle);

}


