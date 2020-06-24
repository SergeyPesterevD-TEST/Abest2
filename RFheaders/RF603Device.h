#ifndef RF603DEVICE_INCLUDE
#define RF603DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RF605Device.h"
#include "RFTypeDefs.h"

namespace RFDevice {

	class RFDEVICE_API RF603Device : public RF605Device
	{
	public:	
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::RF603Device
		/// \brief    Default constructor of RF603Device object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RF603Device(void);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::RF603Device
		/// \brief     Default destructor of RF603Device object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		~RF603Device(void);	

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::EthernetGetStreamMeasure
		/// \brief    Get measures from Ethernet data stream. Input parameter is long pointer to LPRF60xUDPPACKET structure.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL EthernetGetStreamMeasure( LPRF60xUDPPACKET );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::EthernetGetNormalisedStreamMeasure
		/// \brief    Get normalized measures form Ethernet data stream. lpValues is a pointer to float array.
		///           
		/// \return  BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL EthernetGetNormalizedStreamMeasure(float* OUT lpValues);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetCanSpeed
		/// \brief    Set data transfer rate via CAN interface. Input parameter is from 10 to 200.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetCanSpeed( DWORD );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetCanStdID
		/// \brief    Set CAN standard identifier. Input parameter is DWORD value 0...7FFh.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetCanStdID( DWORD );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::
		/// \brief    Set CAN extended identifier. Input parameter is DWORD value 0...1FFFFFFFh.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetCanExtID( DWORD );		

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetCanIdTypeToExt
		/// \brief    Set CAN identifier type to extended.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetCanIdTypeToExt();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetCanIdTypeToStd
		/// \brief    Set CAN identifier to standard.
		///           
		/// \return  BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetCanIdTypeToStd();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::EnableCan
		/// \brief    Change CAN interface power state to turned on/off. bEnable TRUE on on, FALSE on off.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL EnableCan(BOOL bEnable = TRUE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetDestinationIP
		/// \brief    Set destination IP address. dwValue contains IP address.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetDestinationIP(DWORD dwValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetDestinationIP
		/// \brief    Set destination IP address. ucValue[4] is a BYTE array which contains IP address.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetDestinationIP(BYTE ucValue[4]);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetGatewayIP
		/// \brief    Set gateway IP address. dwValue contains IP address.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetGatewayIP(DWORD dwValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetGatewayIP
		/// \brief    Set gateway IP address. ucValue[4] is a BYTE array which contains IP address.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetGatewayIP(BYTE ucValue[4]);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetSubnetMask
		/// \brief    Set subnet mask. dwValue contains subnet mask value.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetSubnetMask(DWORD dwValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetSubnetMask
		/// \brief    Set subnet mask. ucValue[4] is a BYTE array which contains subnet mask value.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetSubnetMask(BYTE ucValue[4]);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetSourceIP
		/// \brief    Set source IP address. dwValue contains IP address.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetSourceIP(DWORD dwValue);	

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::SetSourceIP
		/// \brief    Set source IP address. ucValue[4] is a BYTE array which contains IP address.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL SetSourceIP(BYTE ucValue[4]);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::EnableEth
		/// \brief    Change Ethernet interface power state to turned on/off. bEnable TRUE on on, FALSE on off.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error. 
		//-----------------------------------------------------------------------------
		BOOL EnableEth(BOOL bEnable = TRUE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetCanSpeed
		/// \brief    Get data transfer rate via CAN interface.
		///           
		/// \return   DWORD : 10...200 specifies data transmission rate in increments by 5000 baud.
		//-----------------------------------------------------------------------------
		DWORD GetCanSpeed();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetCanStdID
		/// \brief    Get CAN standard identifier
		///           
		/// \return   DWORD : 0...7FFFh
		//-----------------------------------------------------------------------------
		DWORD GetCanStdID();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetCanExtID
		/// \brief    Get CAN extended identifier.
		///           
		/// \return   DWORD : 0...1FFFFFFFh
		//-----------------------------------------------------------------------------
		DWORD GetCanExtID();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetCanId
		/// \brief    Get any CAN identifier.
		///           
		/// \return   DWORD :
		//-----------------------------------------------------------------------------
		BOOL GetCanId();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetCanState
		/// \brief    Get CAN interface power state.
		///           
		/// \return   BOOL : TRUE on on state, FALSE on off state.
		//-----------------------------------------------------------------------------
		BOOL GetCanState();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetDestinationIP
		/// \brief    Get destination IP address.
		///           
		/// \return   BYTE* : pointer to array which contains IP address.
		//-----------------------------------------------------------------------------
		BYTE* GetDestinationIP();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetHumanReadableDestinationIP
		/// \brief    Get destination IP address in human readable form
		///           
		/// \return   char* : pointer to array of char which contains IP address like ddd.ddd.ddd.ddd
		//-----------------------------------------------------------------------------
		char* GetHumanReadableDestinationIP();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetGatewayIP
		/// \brief    Get gateway IP address.
		///           
		/// \return   BYTE* : pointer to array which contains IP address.
		//-----------------------------------------------------------------------------
		BYTE* GetGatewayIP();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetHumanReadableGatewayIP
		/// \brief    Get gateway IP address in human readable form.
		///           
		/// \return   char* :  pointer to array of char which contains IP address like ddd.ddd.ddd.ddd
		//-----------------------------------------------------------------------------
		char* GetHumanReadableGatewayIP();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetSubnetMask
		/// \brief    Get subnet mask value.
		///           
		/// \return   BYTE* : pointer to array which contains subnet mask.
		//-----------------------------------------------------------------------------
		BYTE* GetSubnetMask();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetHumanReadableSubnetMask
		/// \brief    Get subnet mask in human readable form.
		///           
		/// \return   char* :  pointer to array of char which contains subnet mask like ddd.ddd.ddd.ddd
		//-----------------------------------------------------------------------------
		char* GetHumanReadableSubnetMask();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetSourceIP
		/// \brief    Get device IP address.
		///           
		/// \return   BYTE* : pointer to array which contains IP address.
		//-----------------------------------------------------------------------------
		BYTE* GetSourceIP();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetHumanReadableSourceIP
		/// \brief    Get device IP address in human readable form.
		///           
		/// \return   char* : pointer to array of char which contains IP address like ddd.ddd.ddd.ddd
		//-----------------------------------------------------------------------------
		char* GetHumanReadableSourceIP();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF603Device::GetEthState
		/// \brief    Get Ethernet interface power state.
		///           
		/// \return   BOOL : TRUE on on state, FALSE on off state.
		//-----------------------------------------------------------------------------
		BOOL GetEthState();

	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF603DEVICE_INCLUDE
