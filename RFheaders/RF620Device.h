/********************************************************************
	modified:	2013/04/16
	created:	2013/03/25
	filename: 	RF620Device.h
	author:		RIFTEK, LLC
	
	purpose:	Interface to the RF620 Series LASER SCANNER

	>>>>>>>>>>>><<<<<<<<<<<<<<
	>>>  INTERNAL VERSION  <<<
	>>>>>>>>>>>><<<<<<<<<<<<<<

*********************************************************************/

#ifndef RF620DEVICE_INCLUDE
#define RF620DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFEthernetDevice.h"
#include "RFTypeDefs.h"

namespace RFDevice {

	class RFDEVICE_API RF620Device : public RFEthernetDevice
	{
	public:
#if ((defined _MSC_VER && _MSC_VER >= 1300) || !defined _MSC_VER)
		// Size of raw profile buffer in bytes
		static const size_t ProfileBufferSize = (2 + 2 + 4 * 1024);
		// Size of raw image buffer in bytes
		static const size_t ImageBufferSize = (512 * 640);
		// Number of items in single profile
		static const size_t ProfileValuesCount = (2 * 1024);
#endif

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::RF620Device
		/// \brief    Default constructor of RF620Device object. RF620Device::Connect(UDP_DEVINFOBLOCK_PC * lpDevBlock) must be used to connect to the device over TCP.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RF620Device();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::RF620Device
		/// \brief    Construct RF620Device object assigned to device specified with lpDevBlock structure. RF620Device::Connect() may be used to connect to this device over TCP.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RF620Device(LPUDP_DEVINFOBLOCK_PC lpDevBlock);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::RF620Device
		/// \brief    Default destructor of RF620Device object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		~RF620Device();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::Connect
		/// \brief    Connect to the device via TCP. RF620Device object must be initialized via RF620Device(LPUDP_DEVINFOBLOCK_PC lpDevBlock)
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL Connect();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::Connect
		/// \brief    Connect to the device specified with lpDevBlock via TCP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL Connect(LPUDP_DEVINFOBLOCK_PC lpDevBlock );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::Disconnect
		/// \brief    Disconnect from device when connected via TCP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL Disconnect();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetResult
		/// \brief    Get raw profile buffer from device when connected via TCP. lpBuffer is a pointer to a buffer RF620Device::ProfileBufferSize bytes long.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL GetResult(void* lpBuffer);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetImage
		/// \brief    Get raw image buffer from device's camera  when connected via TCP. lpBuffer is a pointer to a buffer RF620Device::ImageBufferSize bytes long.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL GetImage(void* lpBuffer);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetResultInclinationAngle
		/// \brief    Get result inclination angle value. Device must be connected via TCP.
		///           
		/// \return   short : Angle value (-32767 through 32767) which corresponds to [-60:60] degrees.
		//-----------------------------------------------------------------------------
		short GetResultInclinationAngle();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::ReadParams
		/// \brief    Read internal device parameters. Device must be connected via TCP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL ReadParams();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::WriteParams
		/// \brief    Write internal device parameters. Device must be connected via TCP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL WriteParams();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::FlushParams
		/// \brief    If bDefault is FALSE (by default), function stores current internal device parameters to the EEPROM. If bDefault is set to TRUE, default parameters will be restored. Device must be connected via TCP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL FlushParams(BOOL bDefault = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::UDPConnect
		/// \brief    Connect to the device by UDP. usUDPPort value must be set to valid UDP port number. UDP port number may be obtained with GetHostPortNumber() function. Specific network adapter may be specified with szLocalIPAddress. Otherwise function will bind to 0.0.0.0 (INADDR_ANY).
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL UDPConnect (USHORT usUDPPort, LPCSTR szLocalIPAddress = NULL);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::UDPDisconnect
		/// \brief    Disconnect from device when connected via UDP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL UDPDisconnect();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::UDPGetResult
		/// \brief    Get raw profile buffer from device when connected via UDP. lpBuffer is a pointer to a buffer RF620Device::ProfileBufferSize bytes long.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL UDPGetResult(void* lpBuffer);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::PingTest
		/// \brief    Test if device is available over network by issuing a PING command via TCP.
		///           
		/// \return   BOOL : TRUE if PING reply received, FALSE otherwise.
		//-----------------------------------------------------------------------------
		BOOL PingTest();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::UDPPacketCounter
		/// \brief    Static helper function to extract UDP packet counter from raw packet buffer.
		///           
		/// \return   WORD : UDP packet counter.
		//-----------------------------------------------------------------------------
		static WORD UDPPacketCounter(void* lpBuffer);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::ConvertResultToPoints
		/// \brief    Converts raw profile buffer data specified with lpResultBuffer to the array of DWORD values (lpPointsBuffer). Output values are representations of profile's points in microns. Each odd value of lpPointsBuffer is a X value, and next (even) value is appropriate Z value. lpPointsBuffer must be a pointer to DWORD[RF620Device::ProfileValuesCount]. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value)
		//-----------------------------------------------------------------------------
		USHORT ConvertResultToPoints(void IN *lpResultBuffer, DWORD OUT *lpPointsBuffer, USHORT OUT *lpCount, BOOL bMirror = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetNormalizedResult
		/// \brief    A TCP helper function to get profile data directly to array of DWORD values in microns. See RF620Device::ConvertResultToPoints. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value). Will be 0xFFFF on GetResult failure.
		//-----------------------------------------------------------------------------
		USHORT GetNormalizedResult(DWORD OUT *lpPointsBuffer, USHORT OUT *lpCount, BOOL bMirror = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::UDPGetNormalizedResult
		/// \brief    An UCP helper function to get profile data directly to array of DWORD values in microns. See RF620Device::ConvertResultToPoints. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value). Will be 0xFFFF on UDPGetResult failure.
		//-----------------------------------------------------------------------------
		USHORT UDPGetNormalizedResult(DWORD OUT *lpPointsBuffer, USHORT OUT *lpCount, BOOL bMirror = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::ConvertResultToPoints
		/// \brief    Converts raw profile buffer data specified with lpResultBuffer to the array of float values (lpPointsBuffer). Output values are representations of profile's points in millimeters. Each odd value of lpPointsBuffer is a X value, and next (even) value is appropriate Z value. lpPointsBuffer must be a pointer to float[RF620Device::ProfileValuesCount]. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value)
		//-----------------------------------------------------------------------------
		USHORT ConvertResultToPoints(void IN *lpResultBuffer, float OUT *lpPointsBuffer, USHORT OUT *lpCount, BOOL bMirror = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetNormalizedResult
		/// \brief    A TCP helper function to get profile data directly to array of float values in millimeters. See RF620Device::ConvertResultToPoints. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value). Will be 0xFFFF on GetResult failure.
		//-----------------------------------------------------------------------------
		USHORT GetNormalizedResult(float OUT *lpPointsBuffer, USHORT OUT *lpCount, BOOL bMirror = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetNormalizedResult
		/// \brief    An UDP helper function to get profile data directly to array of float values in millimeters. See RF620Device::ConvertResultToPoints. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value). Will be 0xFFFF on GetResult failure.
		//-----------------------------------------------------------------------------
		USHORT UDPGetNormalizedResult(float OUT *lpPointsBuffer, USHORT OUT *lpCount, BOOL bMirror = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetSerialNumber
		/// \brief    Get serial number of RF620 device.
		///           
		/// \return   DWORD: Device's serial number.
		//-----------------------------------------------------------------------------
		DWORD GetSerialNumber();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetCapsExternalResultSync
		/// \brief    Check if device is capable of external result synchronization.
		///           
		/// \return   BOOL: TRUE or FALSE
		//-----------------------------------------------------------------------------
		BOOL GetCapsExternalResultSync();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetCapsExternalMeasurementSync
		/// \brief    Check if device is capable of external measurement synchronization.
		///           
		/// \return   BOOL: TRUE or FALSE
		//-----------------------------------------------------------------------------
		BOOL GetCapsExternalMeasurementSync();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetCapsAnalogueOutputByCurrent
		/// \brief    Check if device is capable of analogue output synchronization by current.
		///           
		/// \return   BOOL: TRUE or FALSE
		//-----------------------------------------------------------------------------
		BOOL GetCapsAnalogueOutputByCurrent();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetCapsAnalogueOutputByVoltage
		/// \brief    Check if device is capable of analogue output synchronization by voltage.
		///           
		/// \return   BOOL: TRUE or FALSE
		//-----------------------------------------------------------------------------
		BOOL GetCapsAnalogueOutputByVoltage();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetCapsLaserModulation
		/// \brief    Check if device is capable of laser modulation.
		///           
		/// \return   BOOL: TRUE or FALSE
		//-----------------------------------------------------------------------------
		BOOL GetCapsLaserModulation();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetBaseDistance
		/// \brief    Returns device base distance in mm.
		///           
		/// \return   WORD: Base distance in mm.
		//-----------------------------------------------------------------------------
		WORD GetBaseDistance();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetMeasurementRangeZ
		/// \brief    Returns measurement range along Z in mm.
		///           
		/// \return   WORD: Range in mm.
		//-----------------------------------------------------------------------------
		WORD GetMeasurementRangeZ();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetMeasurementRangeXSMR
		/// \brief    Returns measurement range along X(SMR) in mm.
		///           
		/// \return   WORD: Range in mm.
		//-----------------------------------------------------------------------------
		WORD GetMeasurementRangeXSMR();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetMeasurementRangeXEMR
		/// \brief    Returns measurement range along X(EMR) in mm.
		///           
		/// \return   WORD: Range in mm.
		//-----------------------------------------------------------------------------
		WORD GetMeasurementRangeXEMR();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetFirmwareVersion
		/// \brief    Returns device firmware version.
		///           
		/// \return   DWORD: Firmware version number.
		//-----------------------------------------------------------------------------
		DWORD GetFirmwareVersion();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetLaserLevel
		/// \brief    Returns laser emission intensity in the range from 0 (OFF) to 31(maximum power - default).
		///           
		/// \return   BYTE: Laser level.
		//-----------------------------------------------------------------------------
		BYTE GetLaserLevel();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetExposureTime
		/// \brief    Returns exposure time (0 through 65535) which corresponds to 1-65536 microseconds.
		///           
		/// \return   WORD: Exposure time.
		//-----------------------------------------------------------------------------
		WORD GetExposureTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetSignalProcessingTime
		/// \brief    Returns signal processing time (0 through 65535) which corresponds to 1-65536 microseconds.
		///           
		/// \return   WORD: Signal processing time.
		//-----------------------------------------------------------------------------
		WORD GetSignalProcessingTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetLeftBoundary
		/// \brief    Returns left boundary of window dimensions ROI (0 through 224).
		///           
		/// \return   BYTE: Left boundary.
		//-----------------------------------------------------------------------------
		BYTE GetLeftBoundary();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetWindowWidth
		/// \brief    Returns window width (31 through 255).
		///           
		/// \return   BYTE: Window width.
		//-----------------------------------------------------------------------------
		BYTE GetWindowWidth();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetUpperBoundary
		/// \brief    Returns upper boundary window dimensions ROI (0 through 224).
		///           
		/// \return   BYTE: Upper boundary.
		//-----------------------------------------------------------------------------
		BYTE GetUpperBoundary();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetWindowHeight
		/// \brief    Returns window height (31 through 255).
		///           
		/// \return   BYTE: Window height.
		//-----------------------------------------------------------------------------
		BYTE GetWindowHeight();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetExternalResultSyncEnabled
		/// \brief    Checks if external synchronization of result is turned on. Applicable only when RF620Device::GetCapsExternalResultSync() is TRUE.
		///           
		/// \return   BOOL: TRUE if enabled or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetExternalResultSyncEnabled();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetExternalResultSyncEdge
		/// \brief    Returns FALSE if there is leading edge used or TRUE if trailing edge used. Applicable only when RF620Device::GetCapsExternalResultSync() is TRUE.
		///           
		/// \return   BOOL: TRUE or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetExternalResultSyncEdge();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetExternalMeasurementSyncEnabled
		/// \brief    Checks if external synchronization of measurement is turned on. Applicable only when RF620Device::GetCapsExternalMeasurementSync() is TRUE.
		///           
		/// \return   BOOL: TRUE if enabled or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetExternalMeasurementSyncEnabled();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetExternalMeasurementSyncEdge
		/// \brief    Returns FALSE if there is leading edge used or TRUE if trailing edge used. Applicable only when RF620Device::GetCapsExternalMeasurementSync() is TRUE.
		///           
		/// \return   BOOL: TRUE or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetExternalMeasurementSyncEdge();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetAnalogueOutputSyncEnabled
		/// \brief    Checks if synchronization of analogue output is turned on. Applicable only when one of RF620Device::GetCapsAnalogueOutputByCurrent() or RF620Device::GetCapsAnalogueOutputByVoltage() is TRUE.
		///           
		/// \return   BOOL: TRUE if enabled or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetAnalogueOutputSyncEnabled();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetAnalogueOutputSyncEdge
		/// \brief    Returns FALSE if there is leading edge used or TRUE if trailing edge used. Applicable only when one of RF620Device::GetCapsAnalogueOutputByCurrent() or RF620Device::GetCapsAnalogueOutputByVoltage() is TRUE.
		///           
		/// \return   BOOL: TRUE or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetAnalogueOutputSyncEdge();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetAnalogueOutputSyncEdge
		/// \brief    Returns TRUE if level of TTL_OUT0 signal of valid data at the analog output.
		///           
		/// \return   BOOL: TRUE or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetAnalogueOutputTTL_OUT0Level();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetExternalSignalDivisor
		/// \brief    Returns parameter of external signal divisor (0 through 255) which corresponds to 1-256 divisor.
		///           
		/// \return   BYTE: Divisor value.
		//-----------------------------------------------------------------------------
		BYTE GetExternalSignalDivisor();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetMeasurementDelay
		/// \brief    Returns measurement delay time (0 through 255) which corresponds to 0-255 microseconds.
		///           
		/// \return   BYTE: Measurement delay time.
		//-----------------------------------------------------------------------------
		BYTE GetMeasurementDelay();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetAnalogueOutputNumberOfPoints
		/// \brief    Returns a byte value that specifies the number of points at analogue output: 0 - disabled; 1 - 128 points; 2 - 256 points; 3 - 512 points; 4 - 1024 points.
		///           
		/// \return   BYTE: Value in range of 0 through 4.
		//-----------------------------------------------------------------------------
		BYTE GetAnalogueOutputNumberOfPoints();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetAnalogueOutputPointHoldupTime
		/// \brief    Returns point holdup time at the analog output (0 through 255) which corresponds to 1-256 microseconds.
		///           
		/// \return   BYTE: Holdup time.
		//-----------------------------------------------------------------------------
		BYTE GetAnalogueOutputPointHoldupTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetDeviceIPAddress
		/// \brief    Returns device IPv4 address.
		///           
		/// \return   BYTE*: Array of 4 bytes of IPv4 address.
		//-----------------------------------------------------------------------------
		const BYTE *GetDeviceIPAddress();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetHostIPAddress
		/// \brief    Returns IPv4 address of the receiver of UDP package.
		///           
		/// \return   BYTE*: Array of 4 bytes of IPv4 address.
		//-----------------------------------------------------------------------------
		const BYTE *GetHostIPAddress();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetNetworkMask
		/// \brief    Returns Ethernet mask.
		///           
		/// \return   BYTE*: Array of 4 bytes of Ethernet mask.
		//-----------------------------------------------------------------------------
		const BYTE *GetNetworkMask();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetHumanReadableDeviceIPAddress
		/// \brief    Returns device IPv4 address human readable string.
		///           
		/// \return   char*: IPv4 address string. NOTE: String buffer must be deleted by user (use delete[])
		//-----------------------------------------------------------------------------
		char *GetHumanReadableDeviceIPAddress();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetHumanReadableHostIPAddress
		/// \brief    Returns IPv4 address human readable string for UDP package receiver.
		///           
		/// \return   char*: IPv4 address string. NOTE: String buffer must be deleted by user (use delete[])
		//-----------------------------------------------------------------------------
		char *GetHumanReadableHostIPAddress();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetHumanReadableNetworkMask
		/// \brief    Returns human readable string for Ethernet mask.
		///           
		/// \return   char*: Ethernet mask string. NOTE: String buffer must be deleted by user (use delete[])
		//-----------------------------------------------------------------------------
		char *GetHumanReadableNetworkMask();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetHostPortNumber
		/// \brief    Returns port of the receiver of UDP package.
		///           
		/// \return   WORD: UDP port number.
		//-----------------------------------------------------------------------------
		WORD GetHostPortNumber();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetUDPFrequency
		/// \brief    Returns UDP package repetition frequency (0 through 255) which corresponds to 0-255 Hz.
		///           
		/// \return   BYTE: Frequency. If 0 the function is disabled and UDP packages are not transmitted.
		//-----------------------------------------------------------------------------
		BYTE GetUDPFrequency();

		short GetRotationAngle();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetLaserLevel
		/// \brief    Sets laser emission intensity in the range from 0 (OFF) to 31(maximum power - default).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetLaserLevel(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetExposureTime
		/// \brief    Sets exposure time (0 through 65535) which corresponds to 1-65536 microseconds.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExposureTime(WORD wValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetSignalProcessingTime
		/// \brief    Sets signal processing time (0 through 65535) which corresponds to 1-65536 microseconds.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetSignalProcessingTime(WORD wValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetLeftBoundary
		/// \brief    Sets left boundary of window dimensions ROI (0 through 224).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetLeftBoundary(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetWindowWidth
		/// \brief    Sets window width (31 through 255).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetWindowWidth(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetUpperBoundary
		/// \brief    Sets upper boundary window dimensions ROI (0 through 224).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetUpperBoundary(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetWindowHeight
		/// \brief    Sets window height (31 through 255).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetWindowHeight(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::GetExternalResultSyncEnabled
		/// \brief    Turns on/off external synchronization of result. Applicable only when RF620Device::GetCapsExternalResultSync() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExternalResultSyncEnabled(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetExternalResultSyncEdge
		/// \brief    Sets synchronization of result by leading edge if bValue is TRUE, otherwise by trailing edge. Applicable only when RF620Device::GetCapsExternalResultSync() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExternalResultSyncEdge(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetExternalMeasurementSyncEnabled
		/// \brief    Turns on/off external synchronization of measurement. Applicable only when RF620Device::GetCapsExternalMeasurementSync() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExternalMeasurementSyncEnabled(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetExternalResultSyncEdge
		/// \brief    Sets synchronization of measurement by leading edge if bValue is TRUE, otherwise by trailing edge. Applicable only when RF620Device::GetCapsExternalMeasurementSync() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExternalMeasurementSyncEdge(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetAnalogueOutputSyncEnabled
		/// \brief    Turns on/off external synchronization of analogue output. Applicable only when one of RF620Device::GetCapsAnalogueOutputByCurrent() or RF620Device::GetCapsAnalogueOutputByVoltage() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetAnalogueOutputSyncEnabled(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetAnalogueOutputSyncEdge
		/// \brief    Sets synchronization of analogue output by leading edge if bValue is TRUE, otherwise by trailing edge. Applicable only when one of RF620Device::GetCapsAnalogueOutputByCurrent() or RF620Device::GetCapsAnalogueOutputByVoltage() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetAnalogueOutputSyncEdge(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetAnalogueOutputTTL_OUT0Level
		/// \brief    Sets the level of TTL_OUT0 signal of valid data at the analog output.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetAnalogueOutputTTL_OUT0Level(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetExternalSignalDivisor
		/// \brief    Sets parameter of external signal divisor (0 through 255) which corresponds to 1-256 divisor.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExternalSignalDivisor(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetMeasurementDelay
		/// \brief    Sets measurement delay time (0 through 255) which corresponds to 0-255 microseconds.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetMeasurementDelay(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetAnalogueOutputNumberOfPoints
		/// \brief    Sets a byte value that specifies the number of points at analogue output: 0 - disabled; 1 - 128 points; 2 - 256 points; 3 - 512 points; 4 - 1024 points.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetAnalogueOutputNumberOfPoints(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetAnalogueOutputPointHoldupTime
		/// \brief    Sets point holdup time at the analog output (0 through 255) which corresponds to 1-256 microseconds.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetAnalogueOutputPointHoldupTime(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetDeviceIPAddress
		/// \brief    Sets device IPv4 address.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetDeviceIPAddress(BYTE ucValue[4]);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetHostIPAddress
		/// \brief    Sets IPv4 address of the receiver of UDP package.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetHostIPAddress(BYTE ucValue[4]);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetNetworkMask
		/// \brief    Sets Ethernet mask.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetNetworkMask(BYTE ucValue[4]);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetHostPortNumber
		/// \brief    Sets the port of the receiver of UDP package. To avoid conflicts, do not specify values 6000, 6001 and 6002.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetHostPortNumber(WORD wValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetUDPFrequency
		/// \brief    Sets UDP package repetition frequency (0 through 255) which corresponds to 0-255 Hz.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetUDPFrequency(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF620Device::SetUDPFrequency
		/// \brief    Returns the pointer to UDP_DEVINFOBLOCK_PC structure associated to the device.
		///           
		/// \return   const LPUDP_DEVINFOBLOCK_PC: pointer to the UDP_DEVINFOBLOCK_PC structure.
		//-----------------------------------------------------------------------------

		BOOL SetRotationAngle(short sValue);

		const LPUDP_DEVINFOBLOCK_PC GetDevBlock();

		void CloneParameters(RF620Device* lpDev);


//////////////////////////////////////////////////////////////////////////
	private:
		RF620HS_INFO m_DevInfo;
		RF620HS_PARAMETERS m_params;
		UDP_DEVINFOBLOCK_PC m_DevBlock;

		BOOL PopulateParams();
		void UDPPopulateParams();

		BOOL ReadParams(void * lpBuffer);
		BOOL WriteParams(void* lpBuffer);
		BOOL CalcAngle(void* lpBuffer);

	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF620DEVICE_INCLUDE
