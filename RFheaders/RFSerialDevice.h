#ifndef RFCOMDEVICE_INCLUDE
#define RFCOMDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFTypeDefs.h"
#include "serial.h"

#define IS_VALID_PORT(p) (p.comPort>0)

namespace RFDevice {

	class RFDEVICE_API RFSerialDevice : public RFDeviceObject
	{
	public:
		RFSerialDevice();
		~RFSerialDevice();

		/************************************************************************/
		/* RS-232 functions                                                     */
		/************************************************************************/

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFSerialDevice::OpenPort
		/// \brief    Function tries to open serial port for device instance (or assign descriptor assigned to previous succeeded OpenPort call). lpPort_Name is device name (e.g., "COM3" for Windows or "/dev/ttyUSB0" for Linux). dwSpeed specifies baud rate (optional, default rate is used if not specified).
		///           
		/// \return   BOOL :  TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	OpenPort(LPCSTR lpPort_Name, DWORD dwSpeed = BaudDefault);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFSerialDevice::ClosePort
		/// \brief    Try to close serial port for device instance (close port if there is no more instances using this port descriptor).
		///           
		/// \return   BOOL :  TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	ClosePort();

		BOOL    RFDEVICE_DEPRECATED fn_con_DEBUG_REGISTERS(BYTE bAddress, LPcon_DEBUG_REGISTERS con_DEBUG_REGISTERS);

		BOOL	ReadParameter(BYTE bAddress, WORD wParameter, DWORD* lpdwValue);
		BOOL	WriteParameter(BYTE bAddress, WORD wParameter, DWORD dwValue);
		BOOL	ReadCustomParameter(BYTE bAddress, BYTE bParameterAddress, BYTE bParameterSize, void* lpValue);
		BOOL	WriteCustomParameter(BYTE bAddress, BYTE bParameterAddress, BYTE bParameterSize, void* lpValue);
		BOOL	FlushToFlash(BYTE bAddress);
		BOOL	RestoreFromFlash(BYTE bAddress);
		BOOL	LockResult(BYTE bAddress);
		BOOL	GetMeasure(BYTE bAddress, BYTE* lpucBuffer, int nBufLength = 2);
		BOOL	StartStream(BYTE bAddress);
		BOOL	StopStream(BYTE bAddress);
		BOOL	GetStreamMeasure(USHORT* lpusValue);
		BOOL	CustomCmd(char * pcInData, DWORD dwInSize, char * pcOutData, DWORD * pdwOutSize);
		int		GetPortHandle();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::HelloCmd
		/// \brief    Send HelloCmd to device with bAddress address and capture the answer. lprfHelloAnswer pointer to RF60xHELLOANSWER struct.
		///           
		/// \return  BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	HelloCmd(BYTE bAddress, LPRFCOMHELLOANSWER lprfHelloAnswer);

		static BOOL	ValidateData(unsigned char* lpucData, const int nDataLength);

		void GetHelloAnswer(LPRFCOMHELLOANSWER lprfHelloAnswer);

		DWORD SetGetCustomSerialDelay(const DWORD newValue = 0xFFFFFFFF);

	protected:
		DWORD m_dwDefaultBaud;
		DWORD m_dwDelayTimeMS;
		void Serial_Delay(DWORD);
		//BOOL WriteFile_RF(HANDLE, LPCVOID,	DWORD, LPDWORD,	LPOVERLAPPED);
		BOOL AddPortHandle(LPCSTR, DWORD, SerialPort*);
		BOOL RemovePortHandle(SerialPort*);
		int LookupPortHandle(LPCSTR, DWORD, SerialPort*);

		SerialPort m_hCOM;
		RFCOMHELLOANSWER m_helloAnswer;
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RFCOMDEVICE_INCLUDE
