#ifndef RF65XNDEVICE_INCLUDE
#define RF65XNDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RF65xDevice.h"

namespace RFDevice {

	class RFDEVICE_API RF65xNDevice : public RF65xDevice
	{
	public:	
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::RF65xNDevice
		/// \brief    Default constructor of RF65xNDevice object. 
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RF65xNDevice(void);
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::RF65xNDevice
		/// \brief    Default destructor of RF65xNDevice object. 
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		~RF65xNDevice(void);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetSyncType
		/// \brief    Set synchronization type ucValue should be one of next: 0 - asynchronous(min time delay = 100us), 1 - internal timer, 2 - external signal.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetSyncType(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetSamplingPeriod
		/// \brief    Set multiplier/deliver for internal timer/external signal.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetSamplingPeriod(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetRSSync
		/// \brief    Set state of results output for RS interface, dwValue should be on of next: 0 - turned off(no results for output), 1 - asynchronous( as fast as result is ready), 2 - synchronous( according to synchro params ).
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetRSSync(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetRSBaundrate
		/// \brief    Set RS data transfer speed. Speed = dwValue*2400.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetRSBaundrate(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetNetAddress
		/// \brief    Set device address for RS-485 net. 
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetNetAddress(BYTE ucValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::
		/// \brief    Set device laser power to turned on/off state. bValue TRUE on turned on state, FALSE on turned off state.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetPowerState(BOOL bValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetAveragingType
		/// \brief    Set device averaging mode to turned on/off state. dValue 0 on turned off state, 1 on turned on state.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetAveragingType(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetAverageCount
		/// \brief    Set quality of averaging values from 1 to  4096.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetAverageCount(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetResultType
		/// \brief    Set type of measures. dwValue may be next: 0 - one border position, 1 - distance between A and B borders, 2 - object center (B+A)/2, 3 - position of A borderm 4 - position of B border.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetResultType(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetABoundaryNumber
		/// \brief    Set A border number from 0 to 127
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetABoundaryNumber(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetBBoundaryNumber
		/// \brief    Set B border number from 1 to 127
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetBBoundaryNumber(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetAnalogOutSynch
		/// \brief    Set state of results output for Analog interface, dwValue should be on of next: 0 - turned off(no results for output), 1 - asynchronous( as fast as result is ready), 2 - synchronous( according to synchro params ).
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetAnalogOutSynch(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetBeginAnalogOutRange
		/// \brief    Set point in measure range where analog out sets to minimum value
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetBeginAnalogOutRange(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetEndAnalogOutRange
		/// \brief    Set point in measure range where analog out sets to maximum value
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetEndAnalogOutRange(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetZeroPointValue
		/// \brief    Define nominal value 	relatively which measure will be calculated.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetZeroPointValue(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetOutLogicState
		/// \brief    Set device out logic control byte.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetOutLogicState(BYTE ucValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetMinTolerance
		/// \brief    Set down limit.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetMinTolerance(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetMaxTolerance
		/// \brief    Set up limit.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetMaxTolerance(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetEthSynch
		/// \brief    Set state of results output for Ethernet interface, dwValue should be on of next: 0 - turned off(no results for output), 1 - asynchronous( as fast as result is ready), 2 - synchronous( according to synchro params ).
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetEthSynch(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetEthPackType
		/// \brief    Set Ethernet packets type to: 0 on MAC packet, 1 on IP/UDP packet.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetEthPackType(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetEthPackMeasureQuantity
		/// \brief    Set measure quantities in UDP packet from 0 to 255
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetEthPackMeasureQuantity(DWORD dwValue);
		
		BOOL SetEthDestinationMAC(DWORD dwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetEthDestinationMAC
		/// \brief    Set destination MAC address. ucValue is a pointer to char array which contains bytes of address,
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetEthDestinationMAC(BYTE* ucValue);
		
		BOOL SetHumanReadableEthDestinationMAC(LPCSTR szMAC);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetEthSubnetMask
		/// \brief    Set subnet mask. dwValue contains mask value, for example 0xFFFFFF00.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------		
		BOOL SetEthSubnetMask( DWORD dwValue );
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetEthSourceIP
		/// \brief    Set device IP address. dwValue contains address value, for example 0xC0A80002.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetEthSourceIP( DWORD dwValue );
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetEthDestIP
		/// \brief    Set destination IP address. dwValue contains address value, for example 0xC0A80001.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetEthDestIP( DWORD dwValue );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetSyncType
		/// \brief    Get device synchronization type
		///           
		/// \return   BYTE : 0 - asynchronous(min time delay = 100us), 1 - internal timer, 2 - external signal.
		//-----------------------------------------------------------------------------
		BYTE GetSyncType();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetSamplingPeriod
		/// \brief    Get multiplier/deliver for internal timer/external signal.
		///           
		/// \return   DWORD : from 0 to 65535.
		//-----------------------------------------------------------------------------
		DWORD GetSamplingPeriod();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetRSSync
		/// \brief	  Get state of results output for RS interface.
		///           
		/// \return   DWORD : 0 - turned off(no results for output), 1 - asynchronous( as fast as result is ready), 2 - synchronous( according to synchro params ).
		//-----------------------------------------------------------------------------
		DWORD GetRSSync();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetRSBaundrate
		/// \brief    Get RS interface data transfer speed.
		///           
		/// \return   DWORD : speed of transfer 2400, 4800, 7200 and so on.
		//-----------------------------------------------------------------------------
		DWORD GetRSBaundrate();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetNetAddress
		/// \brief    Get device RS-485 net address. 
		///           
		/// \return   BYTE : net address.
		//-----------------------------------------------------------------------------
		BYTE GetNetAddress();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetPowerState
		/// \brief    Get device laser power state.
		///           
		/// \return   BOOL : TRUE on on state, FALSE on off state. 
		//-----------------------------------------------------------------------------
		BOOL GetPowerState();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetAveraging
		/// \brief    Get device averaging state.
		///           
		/// \return   DWORD : 0 on turned off state, 1 on turned on state.
		//-----------------------------------------------------------------------------
		DWORD GetAveraging();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetAverageCount
		/// \brief    Get averaging measures quantity.
		///           
		/// \return   DWORD : quantity of averaging measures.
		//-----------------------------------------------------------------------------
		DWORD GetAverageCount();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetResultType
		/// \brief    Get type of measures. 0 - one border position, 1 - distance between A and B borders, 2 - object center (B+A)/2, 3 - position of A borderm 4 - position of B border.
		///           
		/// \return   DWORD : 0 - one border position, 1 - distance between A and B borders, 2 - object center (B+A)/2, 3 - position of A borderm 4 - position of B border.
		//-----------------------------------------------------------------------------
		DWORD GetResultType();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetABoundaryNumber
		/// \brief    Get A boundary number.
		///           
		/// \return   DWORD : from 0 to 127.
		//-----------------------------------------------------------------------------
		DWORD GetABoundaryNumber();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetBBoundaryNumber
		/// \brief    Get B boundary number.
		///           
		/// \return   DWORD : from 1 to 127.
		//-----------------------------------------------------------------------------
		DWORD GetBBoundaryNumber();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetAnalogOutSynch
		/// \brief    Get state of results output for Analog interface.
		///           
		/// \return   BYTE : 0 - turned off(no results for output), 1 - asynchronous( as fast as result is ready), 2 - synchronous( according to synchro params ).
		//-----------------------------------------------------------------------------
		BYTE GetAnalogOutSynch();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetBeginAnalogOutRange
		/// \brief    Get point in measure range where analog out sets to minimum value.
		///           
		/// \return   DWORD : point value.
		//-----------------------------------------------------------------------------
		DWORD GetBeginAnalogOutRange();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetEndAnalogOutRange
		/// \brief    Get point in measure range where analog out sets to maximum value.
		///           
		/// \return   DWORD : point value.
		//-----------------------------------------------------------------------------
		DWORD GetEndAnalogOutRange();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetZeroPointValue
		/// \brief    Get nominal value 	relatively which measure will be calculated.
		///           
		/// \return   DWORD : nominal value.
		//-----------------------------------------------------------------------------
		DWORD GetZeroPointValue();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetOutLogicState
		/// \brief    Get device out logic control byte.
		///           
		/// \return   BYTE : device out logic control byte.
		//-----------------------------------------------------------------------------
		BYTE GetOutLogicState();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetEthSynch
		/// \brief    Get state of results output for Ethernet interface.
		///           
		/// \return    BYTE : 0 - turned off(no results for output), 1 - asynchronous( as fast as result is ready), 2 - synchronous( according to synchro params ).
		//-----------------------------------------------------------------------------
		BYTE GetEthSynch();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetEthPackType
		/// \brief    Get ethernet packets type. 
		///           
		/// \return   DWORD : 0 on MAC packet, 1 on IP/UDP packet.
		//-----------------------------------------------------------------------------
		DWORD GetEthPackType();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetEthPackMeasureQuantity
		/// \brief    Get measure quantities in UDP packet.
		///           
		/// \return   DWORD : from 0 to 255.
		//-----------------------------------------------------------------------------
		DWORD GetEthPackMeasureQuantity();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetEthDestinationMAC
		/// \brief    Get destination MAC address.
		///           
		/// \return   BYTE* : pointer to array which contains MAC address
		//-----------------------------------------------------------------------------
		BYTE* GetEthDestinationMAC();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetHumanReadableEthDestinationMAC
		/// \brief    Get destination MAC address in readable form 00:00:00:00:00:00:.
		///           
		/// \return   char* : pointer to array of char which contains MAC address
		//-----------------------------------------------------------------------------
		char* GetHumanReadableEthDestinationMAC();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetMinTolerance
		/// \brief    Get down limit.
		///           
		/// \return   DWORD : down limit value.
		//-----------------------------------------------------------------------------
		DWORD GetMinTolerance();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetMaxTolerance
		/// \brief    Get up limit.
		///           
		/// \return   DWORD : up limit value.
		//-----------------------------------------------------------------------------
		DWORD GetMaxTolerance();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetSubnetMask
		/// \brief    Get subnet mask. 
		///           
		/// \return   DWORD : value which contains mask value, for example 0xFFFFFF00.
		//-----------------------------------------------------------------------------
		DWORD GetSubnetMask();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetSourceIP
		/// \brief    Get device IP address.
		///           
		/// \return   DWORD : value which contains IP address.
		//-----------------------------------------------------------------------------
		DWORD GetSourceIP();
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetDestIP
		/// \brief    Get destination IP address.
		///           
		/// \return   DWORD : value which contains destination IP address.
		//-----------------------------------------------------------------------------
		DWORD GetDestIP();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetStreamMeasureN
		/// \brief    Get measure from RS data stream. lpdwValue is a pointer to DWORD value.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL GetStreamMeasureN(DWORD* lpdwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetSingleMeasureN
		/// \brief    Get single measure from device via RS interface. lpdwValue is a pointer to DWORD value.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL GetSingleMeasureN(DWORD* lpdwValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::BufferClear
		/// \brief    Force COM port buffer cleaning.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL BufferClear();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetAnalogCallibrateLow
		/// \brief    Set analog out value at down point. Only for calibrate.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetAnalogCalibrateLow( DWORD dwValue );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetAnalogCalibrateLow
		/// \brief    Get analog out value at down point. Only for calibrate.
		///           
		/// \return   DWORD : down point value.
		//-----------------------------------------------------------------------------
		DWORD GetAnalogCalibrateLow();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetAnalogCalibrateHigh
		/// \brief    Set analog out value at up point. Only for calibrate.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetAnalogCalibrateHigh( DWORD dwValue );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetAnalogCalibrateHigh
		/// \brief    Get analog out value at up point. Only for calibrate.
		///           
		/// \return   DWORD : up point value.
		//-----------------------------------------------------------------------------
		DWORD GetAnalogCalibrateHigh();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetType
		/// \brief    Set type. Only for calibrate.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetType( BYTE ucValue );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetType
		/// \brief    Get type. Only for calibrate.
		///           
		/// \return   BYTE : type value.
		//-----------------------------------------------------------------------------
		BYTE GetType();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetRelease
		/// \brief    Set release. Only for calibrate.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetRelease( BYTE ucValue );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetRelease
		/// \brief    Get type. Only for calibrate.
		///           
		/// \return   BYTE : release value.
		//-----------------------------------------------------------------------------
		BYTE GetRelease();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetBaseDist
		/// \brief    Set base distance. Only for calibrate.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetBaseDist( DWORD dwValue );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetBaseDist
		/// \brief    Get base distance. Only for calibrate.
		///           
		/// \return   DWORD : up point value.
		//-----------------------------------------------------------------------------
		DWORD GetBaseDist();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::SetMeasureRange
		/// \brief    Set measure range. Only for calibrate.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetMeasureRange( DWORD dwValue );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF65xNDevice::GetBaseDist
		/// \brief    Get measure range. Only for calibrate.
		///           
		/// \return   DWORD : up point value.
		//-----------------------------------------------------------------------------
		DWORD GetMeasureRange();
		
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF65XDEVICE_INCLUDE
