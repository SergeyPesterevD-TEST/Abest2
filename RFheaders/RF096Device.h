#ifndef RF096DEVICE_H
#define RF096DEVICE_H

#include "RFDevice.h"
#include "RFEthernetDevice.h"
#include "RFTypeDefs.h"

#if defined(__cplusplus)
extern "C" {
#endif

namespace RFDevice {

class RFDEVICE_API RF096Device :
	public RFEthernetDevice
{
private:
	enum Parameter
	{
		SensorOn		= 0x0001,
		CW				= 0x0201,
		CodDev			= 0x0301,
		UartBaud		= 0x0401,
		ModeRun			= 0x0701,
		SyncConst		= 0x0802,
		ScanningSteps	= 0x0A04,
		ACC				= 0x1002,
		DCC				= 0x1202,
		MAX_SPEED		= 0x1402,
		MIN_SPEED		= 0x1602,
		FS_SPD			= 0x1802,
		STEP_MODE		= 0x1A01,
		CONFIG			= 0x1B01,
		CANbaudRW		= 0x2001,
		StndIdentif		= 0x2202,
		ExtIdentif		= 0x2404,
		CANidentif		= 0x2801,
		CANOn			= 0x2901,
		CANnodeID		= 0x3001,
		NumMeasureOnTurn	= 0x3204,
		R0calibr		= 0x3604,
		Destination_IP	= 0x6C04,
		Gateway_IP		= 0x7004,
		Subnet_Mask		= 0x7404,
		Source_IP		= 0x7804,
		LANmode			= 0x8801,
		DeviceType		= 0x9001,
		SerialNumber	= 0x9202,
		Customer		= 0xA002,
		ParamsVersion	= 0xA202,
		DateFabrication	= 0xC008,
		DateCalibration	= 0xC808,
		ReleaseCPUModule	= 0xD010,
		ReleaseInterfModule	= 0xC010,
		MDESCRIPTOR_ARRAY	= 0xFC04
	};

public:

	RF096Device(void);
	~RF096Device(void);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::Connect
	/// \brief    Establish connection to the device
	/// \param	  szIPAddress: (in) IP address of the device (default is 192.168.0.3)
	/// \param	  wRecvPort: (in) number of UDP port to receive data from the device (default is 6003)
	/// \param	  wSendPort: (in) number of UDP port to send data to the device (default is 6008)
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL Connect(LPCSTR _In_ szIPAddress, const WORD _In_ wRecvPort, const WORD _In_ wSendPort);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::Connect
	/// \brief    Establish connection to the device using default network settings
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL Connect();

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::Disconnect
	/// \brief    Closes connection to the device
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL Disconnect();

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::SetNetAddress
	/// \brief    Change network address (default is 1) in range of 1..127
	/// \param	  bNetAddress: (in) net address value
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL SetNetAddress(const BYTE _In_ bNetAddress);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetNetAddress
	/// \brief    Get network address
	///           
	/// \return   BYTE: network address
	//-----------------------------------------------------------------------------
	BYTE GetNetAddress() const;

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetAssemblyType
	/// \brief    Get assembly type
	///           
	/// \return   WORD: assembly type
	//-----------------------------------------------------------------------------
	WORD GetAssemblyType() const;

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::Hello
	/// \brief    Send hello command and read basic parameters
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL Hello();

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::FlushParams
	/// \brief    Store current parameters to persistent flash
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL FlushParams();

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::RestoreParams
	/// \brief    Restore factory parameters to persistent flash
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL RestoreParams();

	BOOL ResetParamsToFactory();

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetSingleMeasure
	/// \brief    Read single measure to raw buffer
	/// \param	  lpResult: (out) must point to buffer of 96 bytes length
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL GetSingleMeasure(void* _Out_ lpResult);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::StartStream
	/// \brief    Start stream measure
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL StartStream();

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetStreamMeasures
	/// \brief    Read stream measures to raw buffer
	/// \param	  lpResult: (out) must point to buffer of 96 bytes length
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL GetStreamMeasures(void* _Out_ lpResult);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::StopStream
	/// \brief    Stop stream measure
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL StopStream();

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetRecordMeasures
	/// \brief    Read measures from internal file to raw buffer
	/// \param	  wStart: (in) offset in bytes before the last record
	/// \param	  lpResult: (out) must point to buffer of 96 bytes length
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL GetRecordMeasures(const WORD _In_ wStart, void* _Out_ lpResult);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetNormalizedSingleMeasure
	/// \brief    Read single measure to the pair of angle (degree) and distance (mm)
	/// \param	  lpfInclinomenetMeasure: (out) pointer to angle value
	/// \param	  lpfRF603Measure: (out) pointer to distance value
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL GetNormalizedSingleMeasure(float* _Out_ lpfInclinomenetMeasure, float* _Out_ lpfRF603Measure);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetNormalizedStreamMeasures
	/// \brief    Read stream measures to the pair of arrays of angles (degree) and array of distances (mm)
	/// \param	  lpfInclinomenetMeasures: (out) pointer to angle values (array of 96 floats)
	/// \param	  lpfRF603Measures: (out) pointer to distance values (array of 96 floats)
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL GetNormalizedStreamMeasures(float* _Out_ lpfInclinomenetMeasures, float* _Out_ lpfRF603Measures);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetNormalizedRecordMeasures
	/// \brief    Read measures from internal file to the pair of arrays of angles (degree) and array of distances (mm)
	/// \param	  wStart: (in) offset in bytes before the last record
	/// \param	  lpfInclinomenetMeasures: (out) pointer to angle values (array of 96 floats)
	/// \param	  lpfRF603Measures: (out) pointer to distance values (array of 96 floats)
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL GetNormalizedRecordMeasures(const WORD _In_ wStart, float* _Out_ lpfInclinomenetMeasures, float* _Out_ lpfRF603Measures);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::SetEnableSensor
	/// \brief    Turn sensor on and off
	/// \param	  bEnable: (in) TRUE to turn on, FALSE to turn off (power saving mode)
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL SetEnableSensor(const BOOL _In_ bEnable);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::SetScanningSteps
	/// \brief    Set number of scanning steps multiplied to 2 (default is 6400, 0x7ffffff or greater means continuous scanning)
	/// \param	  dwCount: (in) number of scanning steps multiplied to 2
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	//-----------------------------------------------------------------------------
	BOOL SetScanningSteps(const DWORD _In_ dwCount);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::SetDestinationAddress
	/// \brief    Set destination IP address (default is 0xffffffff = 255.255.255.255)
	/// \param	  bAddress: (in) array of 4 bytes representing destination IP address
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	BOOL SetDestinationAddress(const BYTE _In_ bAddress[4]);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::SetGatewayAddress
	/// \brief    Set gateway IP address (default is 0xc0a80001 = 192.168.0.1)
	/// \param	  bAddress: (in) array of 4 bytes representing gateway IP address
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	BOOL SetGatewayAddress(const BYTE _In_ bAddress[4]);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::SetSubnetMask
	/// \brief    Set subnet mask (default is 0xffffff00 = 255.255.255.0)
	/// \param	  bMask: (in) array of 4 bytes representing subnet mask
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	BOOL SetSubnetMask(const BYTE _In_ bMask[4]);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::SetSourceAddress
	/// \brief    Set source IP address (default is 0xc0a80003 = 192.168.0.3)
	/// \param	  bAddress: (in) array of 4 bytes representing source IP address
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	BOOL SetSourceAddress(const BYTE _In_ bAddress[4]);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetEnabledSensor
	/// \brief    Check if sensor is powered on
	/// \param	  lpbEnabled: (out) TRUE if powered on, FALSE if powered off (power saving mode)
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	BOOL GetEnabledSensor(BOOL* _Out_ lpbEnabled);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetScanningSteps
	/// \brief    Get current number of scanning steps multiplied to 2
	/// \param	  lpdwCount: (out) number of scanning steps multiplied to 2
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	BOOL GetScanningSteps(DWORD* _Out_ lpdwCount);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetDestinationAddress
	/// \brief    Get destination IP address
	/// \param	  lpbAddress: (out) array of 4 bytes representing destination IP address
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	BOOL GetDestinationAddress(BYTE _Out_ lpbAddress[4]);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetGatewayAddress
	/// \brief    Get gateway IP address
	/// \param	  lpbAddress: (out) array of 4 bytes representing gateway IP address
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	BOOL GetGatewayAddress(BYTE _Out_ lpbAddress[4]);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetSubnetMask
	/// \brief    Get subnet mask
	/// \param	  lpbMask: (out) array of 4 bytes representing subnet mask
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	BOOL GetSubnetMask(BYTE _Out_ lpbMask[4]);

	//-----------------------------------------------------------------------------
	//  FUNCTION  RF096Device::GetSourceAddress
	/// \brief    Get source IP address
	/// \param	  lpbAddress: (out) array of 4 bytes representing source IP address
	///           
	/// \return   BOOL: TRUE on success, FALSE on error
	BOOL GetSourceAddress(BYTE _Out_ lpbAddress[4]);

private:
	RF096PARAMS m_params;
	RF096HELLOANSWER m_hello;
	BYTE m_datagram[256];
	BYTE m_answer[256];
	WORD m_packetCnt;
	unsigned long m_ulIPAddress;
	WORD m_wSendPort;

	BOOL ReadCustomParam(const BYTE _In_ bAddress, const void* _Out_bytecapcount_(bLength) lpResult, const BYTE _In_ bLength);
	BOOL WriteCustomParam(const BYTE _In_ bAddress, const void* _In_bytecount_(bLength) lpValue, const BYTE _In_ bLength);
	BOOL ExecCommand(const BYTE _In_ bCmd, const BYTE* _In_opt_bytecount_(bDataLen) data = NULL, const BYTE _In_opt_ bDataLen = 0);

	BOOL ReadParam(const RF096Device::Parameter _In_ eParam, void* _Out_ lpResult);
	BOOL WriteParam(const RF096Device::Parameter _In_ eParam, void* _In_ lpValue);
	BOOL WriteParam(const RF096Device::Parameter _In_ eParam, const BYTE _In_ bValue);
	BOOL WriteParam(const RF096Device::Parameter _In_ eParam, const WORD _In_ wValue);
	BOOL WriteParam(const RF096Device::Parameter _In_ eParam, const DWORD _In_ dwValue);
};

}//namespace

#if defined(__cplusplus)
}
#endif

#endif	//RF701DEVICE_H
