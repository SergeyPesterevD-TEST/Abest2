/********************************************************************
	modified:	2014/12/17
	created:	2014/12/05
	filename: 	RF625DDevice.h
	maintainer:	Pavel Filipchik <pfilipchik@riftek.com>
	
	purpose:	Interface to the RF625_DHS Series LASER SCANNER
*********************************************************************/

#ifndef RF625DDEVICE_INCLUDE
#define RF625DDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif
#include "RFDevice.h"
#include "RF625Device_Legacy.h"
#include "RFTypeDefs.h"

namespace RFDevice {

	class RFDEVICE_API RF625Device : public RF625Device_Legacy
	{
	public:
#if ((defined _MSC_VER && _MSC_VER >= 1300) || !defined _MSC_VER)
		// Size of raw profile buffer in bytes
		static const size_t ProfileBufferSize = (12 + 1280 * 16 + 4 + 512);
		// Size of raw image buffer in bytes
		static const size_t ImageBufferSize = (480 * 640);
		// Number of items in single profile
		static const size_t ProfileValuesCount = (2 * 1280*4);
#endif

		RF625Device(const DWORD dwOwnerPID = 0);
		RF625Device(LPUDP_DEVINFOBLOCK_PC lpDevBlock, const DWORD dwOwnerPID = 0);
		virtual ~RF625Device();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::ReadParams
		/// \brief    Read parameters from device. Device must be connected with Connect().
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------

		BOOL ReadParams();
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::WriteParams
		/// \brief    Write parameters to device. Device must be connected with Connect().
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------

		BOOL WriteParams(BOOL bVerify = FALSE);
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetResult
		/// \brief    Get measurement packet from device. Device must be connected with Connect().
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------

		BOOL GetResult(void* lpBuffer);
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetExtends
		/// \brief    Get extended information packet from device. Device must be connected with Connect().
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL GetExtends(void* lpBuffer);

#ifdef RFDEVICE_FACTORY_API
		BOOL GetImage(void* lpBuffer, BOOL bDeinterlaceDHS = TRUE);
#else
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetImage
		/// \brief    Get image buffer from device. Device must be connected with Connect().
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL GetImage(void* lpBuffer);
#endif

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::ReadParams
		/// \brief    Read parameters from device to buffer (must be preallocated, 512 bytes long). Device must be connected with Connect().
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL ReadParams(void *lpBuffer) {return RF625Device_Legacy::ReadParams(lpBuffer);}

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetLaserLevel
		/// \brief    Set laser power level. Range is 0(off) to 255(max power). Must call WriteParams() to apply setting.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetLaserLevel(BYTE ucValue);
#ifdef RFDEVICE_FACTORY_API
		RF_customer_id GetCustomerId();
		BOOL GetPixels(void* lpBuffer);
#endif
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::ConvertResultToPoints
		/// \brief    Make points array from raw result buffer filled by GetResult() call.
		/// \details  lpResultBuffer is a pointer to array of float, ProfileValuesCount length. Each even element is used to store X value, each odd element is used to store appropriate Z value (in millimeters).\n
		///			  lpMeasureCnt and lpPacketCnt are optional pointers to USHORT variables set to sequential measurement number and packet number of not NULL.
		///           
		/// \return   USHORT : Number of points on success, 0xFFFF on error.
		//-----------------------------------------------------------------------------
		USHORT ConvertResultToPoints(void IN *lpResultBuffer, float OUT *lpPointsBuffer, USHORT OUT *lpCount, USHORT *lpMeasureCnt = NULL, USHORT *lpPacketCnt = NULL, BOOL bChecksumCheck = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetNormalizedResult
		/// \brief    Get measurement packet as points array. Device must be connected with Connect().
		/// \details  lpResultBuffer is a pointer to array of float, ProfileValuesCount length.\n
		///			  lpMeasureCnt and lpPacketCnt are optional pointers to USHORT variables set to sequential measurement number and packet number of not NULL.
		///           
		/// \return   USHORT : Number of points on success, 0xFFFF on error.
		//-----------------------------------------------------------------------------
		USHORT GetNormalizedResult(float OUT *lpPointsBuffer, USHORT OUT *lpCount, USHORT *lpMeasureCnt = NULL, USHORT *lpPacketCnt = NULL);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::UDPGetNormalizedResult
		/// \brief    Get measurement packet as points array when sensor operating in UDP stream mode. Device must be connected with UDPConnect().
		/// \details  lpResultBuffer is a pointer to array of float, ProfileValuesCount length.\n
		///			  lpMeasureCnt and lpPacketCnt are optional pointers to USHORT variables set to sequential measurement number and packet number of not NULL.
		///           
		/// \return   USHORT : Number of points on success, 0xFFFF on error.
		//-----------------------------------------------------------------------------
		USHORT UDPGetNormalizedResult(float OUT *lpPointsBuffer, USHORT OUT *lpCount, USHORT *lpMeasureCnt = NULL, USHORT *lpPacketCnt = NULL);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetFrequency
		/// \brief    Returns current frequency of UDP stream.
		///           
		/// \return   WORD : Value of frequency in Hz.
		//-----------------------------------------------------------------------------
		WORD GetFrequency();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetAutoExposure
		/// \brief    Sets value of lpusValue pointer to current exposure time when auto exposure is turned on. lpusValue must not be NULL.\n
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL GetAutoExposure(LPWORD lpusValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetFrequency
		/// \brief    Set UDP stream frequency to wValue Hz. Limited to 250 for HS mode and 500 for DHS mode. Must call WriteParams() to apply setting.\n
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetFrequency(WORD wValue);

		WORD GetExternalSignalDivisor();
		
		BOOL SetExternalSignalDivisor(WORD wValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetTCPPortNumber
		/// \brief    Get number of TCP port on which sensor runs its TCP service. By default sensor uses port 620.\n
		///           
		/// \return   WORD : A port number.
		//-----------------------------------------------------------------------------
		WORD GetTCPPortNumber();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetTCPPortNumber
		/// \brief    Set number of TCP port on which sensor runs its TCP service. Must call WriteParams() to apply setting.
		/// \details  TCP service will use new port after reboot. Recommended values are >=1024. Port 6001 cannot be used.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetTCPPortNumber(WORD wValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetEnableDHS
		/// \brief    Returns TRUE if DHS mode is enabled, FALSE if sensor works in HS mode.
		///           
		/// \return   BOOL :
		//-----------------------------------------------------------------------------
		BOOL GetEnableDHS();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetEnableDHS
		/// \brief    Turns on and off the DHS mode. Must call WriteParams() to apply setting. 
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetEnableDHS(BOOL bEnable);
		
		BYTE GetDifBrightness();
		
		BOOL SetDifBrightness(BYTE ucValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetUpperBoundary
		/// \brief    Get upper boundary of ROI window.
		///           
		/// \return   WORD :
		//-----------------------------------------------------------------------------
		WORD GetUpperBoundary();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetWindowHeight
		/// \brief    Get height of ROI window.
		///           
		/// \return   WORD :
		//-----------------------------------------------------------------------------
		WORD GetWindowHeight();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetUpperBoundary
		/// \brief    Set value of upper boundary of ROI window. wValue must be multiple of 32. Maximum value is 447. Must call WriteParams() to apply setting.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetUpperBoundary(WORD wValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetWindowHeight
		/// \brief    Set value of height of ROI window. wValue must be multiple of 32. Valid range is [32..480]. Must call WriteParams() to apply setting.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetWindowHeight(WORD wValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetKeepTCPEnabled
		/// \brief    Returns TRUE if KeepTCP feature enabled, FALSE otherwise. See SetKeepTCP() for explanation.
		///           
		/// \return   BOOL :
		//-----------------------------------------------------------------------------
		BOOL GetKeepTCPEnabled();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetKeepTCPTime
		/// \brief    Get KeepTCP timeout in seconds.
		///           
		/// \return   WORD :
		//-----------------------------------------------------------------------------
		WORD GetKeepTCPTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetKeepTCP
		/// \brief    Turns on or off KeepTCP feature. wTime specifies KeepTCP timeout in seconds and ignored if bEnabled is set to FALSE. Must call WriteParams() to apply setting.
		/// \details  The purpose of KeepTCP feature is to change TCP connection keep-alive time from default socket setting in sensor firmware (about 2 seconds).\n
		///			  If no packet comes to the TCP service it will abort connection to host after idle time counter becomes wTime. If any packet will be read by TCP service idle time counter sets to 0.\n
		///			  The reason of using of this feature is case of when your TCP session was down before you called Disconnect() to shut it down gracefully.\n
		///			  TCP service will close session after specified amount of time and will be ready for new connection. Setting KeepTCP timeout to large values will make sensor unresposnsible to incoming TCP connections.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetKeepTCP(BOOL bEnable, WORD wTime = 0);

		BOOL GetFilterEnabled();
		
		WORD GetFilterParam();
		
		BOOL SetFilter(BOOL bEnable, WORD wParam = 0);
		
		BOOL GetSmoothEnabled();

		WORD GetSmoothParam();

		BOOL SetSmooth(BOOL bEnable, WORD wParam = 0);

		// Future implementation.
		BYTE GetROIAH();

		// Future implementation.
		BYTE GetROIAP();

		// Future implementation.
		BOOL SetROIAH(BYTE ucAH);

		// Future implementation.
		BOOL SetROIAP(BYTE ucAP);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetROIEnabled
		/// \brief    Returns TRUE if ROI is enabled, otherwise FALSE.
		///           
		/// \return   BOOL : ROI state.
		//-----------------------------------------------------------------------------
		BOOL GetROIEnabled();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetROI
		/// \brief    Enable or disable ROI and set ROI parameters
		/// \details  If bEnable is FALSE ROI will be turned off, other parameters has no effect and shouldn't be passed to function call.\n
		///			  If bEnable is TRUE ROI will be turned on.\n
		///			  wUpperBoundary is upper coordinate of ROI window, it must be multiple of 32. Maximum value is 447.\n
		///			  wWindowHeight is value of height of ROI window. wValue must be multiple of 32. Valid range is [32..480].\n
		///			  ucAP and ucAH are reserved, must be 0.\n
		///			  Must call WriteParams() to apply setting.
		///           
		/// \return   BOOL : TRUE on success, otherwise FALSE.
		//-----------------------------------------------------------------------------
		BOOL SetROI(BOOL bEnable, WORD wUpperBoundary = 0, WORD wWindowHeight = 0, BYTE ucAP = 0, BYTE ucAH = 0);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetAnalogEnabled
		/// \brief    Returns TRUE if analog out is enabled, otherwise FALSE.
		///           
		/// \return   BOOL : Analog out state.
		//-----------------------------------------------------------------------------
		BOOL GetAnalogEnabled();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetAnalog
		/// \brief    Enable or disable analog out.\n
		/// \details  If bEnable is FALSE analog out will be turned off, other parameters has no effect and shouldn't be passed to function call.\n
		///			  If bEnable is TRUE analog out will be turned on.\n
		///			  ucType is analog out type.\n
		///			  Must call WriteParams() to apply setting.
		///           
		/// \return   BOOL : TRUE on success, otherwise FALSE.
		//-----------------------------------------------------------------------------
		BOOL SetAnalog(BOOL bEnable, BYTE ucType = 0);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetSync
		/// \brief    Set sync parameters.
		/// \details  wType: 0 : turned off, 1 : internal, 2 : external, 3 : encoder.\n
		///			  wChannels: channel number (0..3).\n
		///			  ucMeasureSync: 1 to enable measurement sync.\n
		///			  wFreq: internal sampling frequency.\n
		///			  wDelay: delay in microseconds.\n
		///			  ucDivider: signal divider.\n
		///			  Must call WriteParams() to apply setting.
		///           
		/// \return   BOOL : TRUE on success, otherwise FALSE.
		//-----------------------------------------------------------------------------
		BOOL SetSync(WORD wType, WORD wChannels, BYTE ucMeasureSync, WORD wFreq, WORD wDelay, BYTE ucDivider);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetSyncType
		/// \brief    Returns sync type.
		///           
		/// \return   WORD :
		//-----------------------------------------------------------------------------
		WORD GetSyncType();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetSyncChannels
		/// \brief    Returns sync channel number.
		///           
		/// \return   WORD :
		//-----------------------------------------------------------------------------
		WORD GetSyncChannels();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetSyncMeasure
		/// \brief    Returns measurement sync state.
		///           
		/// \return   BYTE :
		//-----------------------------------------------------------------------------
		BYTE GetSyncMeasure();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetSyncFreq
		/// \brief    Returns internal sampling frequency.
		///           
		/// \return   WORD :
		//-----------------------------------------------------------------------------
		WORD GetSyncFreq();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetSyncDelay
		/// \brief    Returns sync delay in microseconds.
		///           
		/// \return   WORD :
		//-----------------------------------------------------------------------------
		WORD GetSyncDelay();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetSyncDivider
		/// \brief    Returns sync signal divider.
		///           
		/// \return   BYTE :
		//-----------------------------------------------------------------------------
		BYTE GetSyncDivider();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetUDPStream
		/// \brief    Turns on and off the UDP stream. Must call WriteParams() to apply setting. 
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetUDPStream(BOOL bEnable);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetUDPStreamEnabled
		/// \brief    Returns UDP stream enabled state.
		///           
		/// \return   BOOL :
		//-----------------------------------------------------------------------------
		BOOL GetUDPStreamEnabled();

		BOOL SetAveraging(BOOL bEnable);

		BOOL GetAveragingEnabled();

		BOOL SetDropCountersExt(BYTE ucTimeoutSec);

		BYTE GetDropCountersExt();

		BOOL SetDropCountersInt(BYTE ucTimeoutSec);

		BYTE GetDropCountersInt();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::SetInterpolation
		/// \brief    Set sample size.
		/// \details  ucType: one of the following values: 0 : 80, 1 : 160, 2 : 320, 3 : 640, 4 : 1280.\n
		///			  Must call WriteParams() to apply setting.
		///           
		/// \return   BOOL : TRUE on success, otherwise FALSE.
		//-----------------------------------------------------------------------------
		BOOL SetInterpolation(BYTE ucType);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625DDevice::GetInterpolation
		/// \brief    Returns sample size type.
		///           
		/// \return   BYTE : See SetInterpolation() for meaning.
		//-----------------------------------------------------------------------------
		BYTE GetInterpolation();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetExposureTime
		/// \brief    Sets exposure time (value in microseconds).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExposureTime(WORD wValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetExposureTime
		/// \brief    Returns exposure time (value in microseconds).
		///           
		/// \return   WORD: Exposure time.
		//-----------------------------------------------------------------------------
		WORD GetExposureTime();




		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetXInverted
		/// \brief    Sets profile inverted by X.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetXInverted(BOOL value);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetZInverted
		/// \brief    Sets profile inverted by Z.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetZInverted(BOOL value);


		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetXInverted
		/// \brief    Returns 1 if scanner gives X inverted profile.
		///           
		/// \return   BYTE: X inverted.
		//-----------------------------------------------------------------------------
		BYTE GetXInverted();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetZInverted
		/// \brief    Returns 1 if scanner gives Z inverted profile.
		///           
		/// \return   BYTE: Z inverted.
		//-----------------------------------------------------------------------------
		BYTE GetZInverted();


		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::EnableLocalSAP
		/// \brief    Sets local SAP enabled.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetEnableLocalSAP(BYTE value);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::EnableLocalSAP
		/// \brief    Get local SAP enabled.
		///           
		/// \return   BYTE: return 1 if local SAP enabled or 0.
		//-----------------------------------------------------------------------------
		BYTE GetEnableLocalSAP();
















#ifdef RFDEVICE_FACTORY_API
		BOOL SaveUserParamsToXml(LPCSTR szFilename = NULL);
		static BOOL SendEmergencyBlock(const LPRF625DHS_EMERGENCY_BLOCK lpBlock);
		BOOL SendSPI(BYTE lpucValues[4]);
#endif

		// Stubs for obsolete methods
	private:
		RFDEVICE_DEPRECATED inline WORD GetSignalProcessingTime() {return 0;}
		RFDEVICE_DEPRECATED inline BOOL SetSignalProcessingTime(WORD wValue) {return FALSE;}
		RFDEVICE_DEPRECATED inline BYTE GetMeasurementDelay() {return 0;}
		RFDEVICE_DEPRECATED inline BOOL SetMeasurementDelay(BYTE ucValue) {return FALSE;}
		RFDEVICE_DEPRECATED inline BYTE GetAnalogueOutputNumberOfPoints() {return 0;}
		RFDEVICE_DEPRECATED inline BOOL SetAnalogueOutputNumberOfPoints(BYTE ucValue) {return FALSE;}
		RFDEVICE_DEPRECATED inline BYTE GetAnalogueOutputPointHoldupTime() {return 0;}
		RFDEVICE_DEPRECATED inline BOOL SetAnalogueOutputPointHoldupTime(BYTE ucValue) {return FALSE;}
		//RFDEVICE_DEPRECATED inline BYTE GetUpperBoundary() {return 0;};
		//RFDEVICE_DEPRECATED inline BYTE GetWindowHeight() {return 0;};
		RFDEVICE_DEPRECATED inline BOOL SetUpperBoundary(BYTE ucValue) {return FALSE;};
		RFDEVICE_DEPRECATED inline BOOL SetWindowHeight(BYTE ucValue) {return FALSE;};
		RFDEVICE_DEPRECATED inline BOOL SetEnableInterpolation(BOOL bEnable) {return FALSE;}

	private:
		RF625DHS_PARAMETERS m_params_dhs;

		BOOL PopulateParams();
		void UDPPopulateParams();

		BOOL RegisterOwnerPID(const DWORD dwOwnerPID);

	};
}//namespace

#if defined(__cplusplus)
}
#endif

#endif //RF625DDevice_INCLUDE
