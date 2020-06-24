#include "../inc/hidapi.h"

#include <stdint.h>
#include <vector>
#include <list>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <wchar.h>

using namespace std;

#ifndef QHIDAPI_H
#define QHIDAPI_H

typedef struct hid_device_info HID_DEVICE_INFO;

class QHidApi
{
    hid_device *handle; //!< Device handle
    // Enumerate and print the HID devices on the system
    HID_DEVICE_INFO *devs;
    bool open;      //!< open > 1 device
    int32_t n_dev;   //!< quantity found devices
    unsigned char buf[250];

	vector<HID_DEVICE_INFO> skbis_dev;
    

public:
    QHidApi();
    QHidApi(uint16_t PID, uint16_t VID);

    ~QHidApi(){
        close_dev();
    }

    list<wstring> get_all_devices(){
		list<wstring> list_devices;
        wstring cur_dev_desc;
        HID_DEVICE_INFO *cur_dev = devs;

        uint16_t i = 0;
        while(cur_dev){
            cur_dev_desc.clear();
			wchar_t str[200];

			swprintf_s(str, sizeof(str) / sizeof (str[0]), L"------------------Device №%d------------------\nPID: 0x%02X\nVID: 0x%02X\n", i++, cur_dev->product_id, cur_dev->vendor_id);	
            cur_dev_desc.append(str);

            swprintf_s(str, sizeof(str) / sizeof (str[0]), L"path: %s\nserial number: %s\n", cur_dev->path, cur_dev->serial_number);
			cur_dev_desc.append(str);

			swprintf_s(str, sizeof(str) / sizeof (str[0]), L"Manufacturer: %s\nProduct: %s\n\n", cur_dev->manufacturer_string, cur_dev->product_string);
			cur_dev_desc.append(str);

			list_devices.push_back(cur_dev_desc);;
            cur_dev = cur_dev->next;
        }

        return list_devices;
    }

    bool get_skbis_devices(list<wstring> &list_d){
        wstring cur_dev_desc;
        HID_DEVICE_INFO *cur_dev;

        cur_dev = hid_enumerate(0, 0);
        n_dev = 0;
        list_d.clear();
        skbis_dev.clear();
		char skbisStr[] = "SKBIS";

        while(cur_dev){
		
			char manufacturer[100];
			size_t strlenw = wcslen(cur_dev->manufacturer_string);
            wcstombs_s(&strlenw, manufacturer, sizeof(manufacturer),
                    cur_dev->manufacturer_string, sizeof(manufacturer) / sizeof(manufacturer[0]));


            if( strcmp(skbisStr, manufacturer) == 0 ){
                skbis_dev.push_back(*cur_dev);


				wchar_t dev_info_str[100];
				swprintf_s(dev_info_str, L"Device: %s, Serial: %s", cur_dev->product_string, cur_dev->serial_number);
                cur_dev_desc.clear();
				cur_dev_desc.append(dev_info_str);

                list_d.push_back( cur_dev_desc );
                n_dev++;
            }
            cur_dev = cur_dev->next;
        }
        if(!n_dev) return false;

        return true;
    }

   bool get_skbis_devices(){
        HID_DEVICE_INFO *cur_dev = devs;
		char skbisStr[] = "SKBIS";

        while(cur_dev){

			char manufacturer[100];
			size_t manSize = sizeof(manufacturer);
			wcstombs_s(&manSize, manufacturer, cur_dev->manufacturer_string, sizeof(manufacturer) / sizeof(manufacturer[0]));
			if (strcmp(skbisStr, manufacturer) == 0){
				skbis_dev.push_back(*cur_dev);
            }
            cur_dev = cur_dev->next;
        }
        if(skbis_dev.size()){
            return true;
        }

        return false;


    }

    bool is_open(){
        return open;
    }

    uint32_t get_n_devices(){
        return skbis_dev.size();
    }

    /**
     * @brief open
     * Open USB HID device for exchange
     * @param n - number openning device: 0..get_n_devices() - 1 if(get_n_devices())
     * @return - status: true open ok, false open fail
     */
    bool open_dev(uint32_t n){
        if(open) close_dev();

        handle = 0;
        open = false;

        if(get_n_devices() >= n + 1){
            HID_DEVICE_INFO *cd = &skbis_dev[n];
            handle = hid_open(cd->vendor_id, cd->product_id, cd->serial_number);
            if(handle == NULL) open = false;
            else open = true;
        }

        return open;
    }

    void close_dev(){
        if(open){
            hid_close(handle);
            open = false;
        }
    }

    /**
    * @brief read_stream
    * Read current coordinate witch timestamp
    * @return
    */
    uint32_t read_stream(uint8_t* Buff){
        if(open){
            Buff[0] = 0;
            //return hid_read(handle, buf, sizeof(buf));
            uint32_t res = hid_read_timeout(handle, Buff, sizeof(buf), 100);
             if(res == 0xFFFFFFFF) res = 0;
            // return true;
            return res;
        }
        return false;
    }

    bool write_stream(uint8_t* Buff, uint8_t ByteNum){
        if(open){
            buf[0] = 0;
            for(uint8_t i = 0; i < ByteNum; i++){
                buf[1 + i] = Buff[i];
            }
            return hid_write(handle, buf, sizeof(buf));
        }
        return false;
    }
};

#endif // QHIDAPI_H
