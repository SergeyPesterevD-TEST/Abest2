#ifndef RF60XDEVICE_INCLUDE
#define RF60XDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFSerialDevice.h"
#include "RFTypeDefs.h"

namespace RFDevice {

	class RFDEVICE_API RF60xDevice : public RFSerialDevice
	{
	public:
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::RF60xDevice
		/// \brief    Default constructor of RF60xDevice object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RF60xDevice(void);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::RF60xDevice
		/// \brief    Default destructor of RF603Device object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		~RF60xDevice(void);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::BindNetworkAddress
		/// \brief    Bind RS-485 net address.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		void	BindNetworkAddress(BYTE ucAddress);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::GetTimeouts
		/// \brief    Get serial port timeouts. lpdwReadIntervalTimeout, lpdwReadTotalTimeoutMultiplier, lpdwReadTotalTimeoutConstant, lpdwWriteTotalTimeoutMultiplier, lpdwWriteTotalTimeoutConstant are pointers to DWORD values.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	GetTimeouts(LPDWORD lpdwReadIntervalTimeout, LPDWORD lpdwReadTotalTimeoutMultiplier, 
							LPDWORD lpdwReadTotalTimeoutConstant, LPDWORD lpdwWriteTotalTimeoutMultiplier, 
							LPDWORD lpdwWriteTotalTimeoutConstant);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetTimeouts
		/// \brief    Set serial port timeouts. lpdwReadIntervalTimeout, lpdwReadTotalTimeoutMultiplier, lpdwReadTotalTimeoutConstant, lpdwWriteTotalTimeoutMultiplier, lpdwWriteTotalTimeoutConstant are pointers to DWORD values.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetTimeouts(DWORD dwReadIntervalTimeout, DWORD dwReadTotalTimeoutMultiplier, 
							DWORD dwReadTotalTimeoutConstant, DWORD dwWriteTotalTimeoutMultiplier, 
							DWORD dwWriteTotalTimeoutConstant);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::GetStreamMeasures
		/// \brief    Get measures from RS data stream. 
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	GetStreamMeasures(LPRF60xSTREAMVALUE lpusStreamValues, DWORD dwMeasuresCount, 
								  LPDWORD lpdwReadedMeasuresCount, LPDWORD lpdwBrokenPacketsCount);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::GetSingleMeasure
		/// \brief    Get single measure from sensor through serial port.
		///           
		/// \return   float : measured value
		//-----------------------------------------------------------------------------
		BOOL   GetSingleMeasure(LPWORD lpwValue);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::GetNormalizedMeasure
		/// \brief    Get normalized single measure from sensor through serial port.
		///           
		/// \return   float : measured value
		//-----------------------------------------------------------------------------
		float GetNormalizedMeasure();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::EnableSensor
		/// \brief    Set sensor laser power state to turned on/off state. bEnable TRUE on on state, FALSE on off state.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	EnableSensor(BOOL bEnable = TRUE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::EnableAnalogOut
		/// \brief    Set analog out power state to turned on/off state. bEnable TRUE on on state, FALSE on off state.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	EnableAnalogOut(BOOL bEnable = TRUE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetSampleAveraging
		/// \brief    Set averaging, sampling, and AL output control byte. ucValue contains control byte.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetSampleAveraging(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetAverageModeByQuantity
		/// \brief    Set quantity averaging mode.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetAverageModeByQuantity();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetAverageModeByTime
		/// \brief    Set time averaging mode.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetAverageModeByTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetCANModeByRequest
		/// \brief    Set request mode of CAN interface.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetCANModeByRequest();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetCANModeByClk
		/// \brief    Set synchronization mode of CAN interface.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetCANModeByClk();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetLogicOutModeToRangeOverflow
		/// \brief    Set logical output mode to out of range indication mode.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetLogicOutModeToRangeOverflow();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetLogicOutModeToMutualSynchronization
		/// \brief    Set logical output mode to mutual synchronization mode.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetLogicOutModeToMutualSynchronization();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetLogicOutModeToResZeroing
		/// \brief    Set logical output mode to hardware zero set mode.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetLogicOutModeToResZeroing();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetLogicOutModeToLaserPower
		/// \brief    Set logical output mode to laser turn OFF/ON mode.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetLogicOutModeToLaserPower();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetAnalogOutModeToFrameMode
		/// \brief    Set analog output mode to window mode.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetAnalogOutModeToFrameMode();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetAnalogOutModeToFullMode
		/// \brief    Set analog output mode to full range mode.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetAnalogOutModeToFullMode();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetSampleModeToTime
		/// \brief    Set sampling mode to time sampling.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetSampleModeToTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetSampleModeToClk
		/// \brief    Set sampling mode to trigger sampling.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetSampleModeToClk();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetNetworkAddress
		/// \brief    Set RS-485 network address. uc Value is network address.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------		
		BOOL	SetNetworkAddress(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetBaundRate
		/// \brief    Set data transfer rate in increments of 2400 baud. dwValue is from 1 to 192.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetBaundRate( DWORD dwValue );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetAverageCount
		/// \brief    Set number of averaged value. dwValue is from 1 to 128.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetAverageCount( DWORD dwValue );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetSamplingPeriod
		/// \brief    Set sampling multiplier/deliver. Input parameter is DWORD value from 1 to 65535 for trigger sampling and from 10 to 65535 for time sampling.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetSamplingPeriod( DWORD );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetAccumulationTime
		/// \brief    Set integration time for CMOS-array in increments of 1mks. Input parameter is DWORD value from 2 to 65535.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetAccumulationTime( DWORD );	

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetBeginAnalogRange
		/// \brief    Specify a point within the absolute range of transducer where  the analog output has a minimum value. Input parameter is DWORD value.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetBeginAnalogRange( DWORD );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetEndAnalogRange
		/// \brief    Specify a point within the absolute range of transducer where  the analog output has a maximum value. Input parameter is DWORD value.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetEndAnalogRange( DWORD );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetResultDelayTime
		/// \brief    Set time interval in increments of 5ms. Input parameter is DWORD value.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetResultDelayTime( DWORD );	

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::SetZeroPointValue
		/// \brief    Set beginning of absolute coordinate system. Input parameter is DWORD value.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL	SetZeroPointValue( DWORD );	
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::GetPowerState
		/// \brief    Get device laser power state
		///           
		/// \return   BOOL : TRUE on on state, FALSE on off state.
		//-----------------------------------------------------------------------------
		BOOL	GetPowerState();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    Get device analog out power state
		///           
		/// \return   BOOL : TRUE on on state, FALSE on off state.
		//-----------------------------------------------------------------------------
		BOOL	GetAnalogOut();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::GetSampleAveraging
		/// \brief    Get averaging, sampling, and AL output control byte. 
		///           
		/// \return   BYTE : value which contains control byte.
		//-----------------------------------------------------------------------------
		BYTE	GetSampleAveraging();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::IsAverageModeByTime
		/// \brief    Check if averaging mode is time mode
		///           
		/// \return   BOOL : TRUE on time mode, FALSE on quantity mode.
		//-----------------------------------------------------------------------------
		BOOL	IsAverageModeByTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::IsCANModeBySynch
		/// \brief    Check if CAN interface mode is synchronization mode.
		///           
		/// \return   BOOL : TRUE on synchronization mode, FALSE on request mode.
		//-----------------------------------------------------------------------------
		BOOL	IsCANModeBySynch();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::GetLogicOutMode
		/// \brief    Get out logic mode.
		///           
		/// \return   BYTE : 00 on out of range indication, 01 mutual synchronization mode, 10 on hardware zero set mode, 11 on laser turn on/off.
		//-----------------------------------------------------------------------------
		BYTE	GetLogicOutMode();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::IsAnalogOutModeFull
		/// \brief    Check if analog out mode if full range mode.
		///           
		/// \return   BOOL : TRUE on full range mode, FALSE on window mode.
		//-----------------------------------------------------------------------------
		BOOL	IsAnalogOutModeFull();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::IsSampleModeClk
		/// \brief    Check if sample mode is trigger sampling mode.
		///           
		/// \return   BOOL : TRUE on trigger sampling mode, FALSE on time sampling mode.
		//-----------------------------------------------------------------------------
		BOOL	IsSampleModeClk();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    
		///           
		/// \return    : 
		//-----------------------------------------------------------------------------
		BYTE	GetNetworkAddress();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    
		///           
		/// \return    : 
		//-----------------------------------------------------------------------------
		DWORD	GetBaundRate();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    
		///           
		/// \return    : 
		//-----------------------------------------------------------------------------
		DWORD	GetAverageCount();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    
		///           
		/// \return    : 
		//-----------------------------------------------------------------------------
		DWORD	GetSamplingPeriod();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    
		///           
		/// \return    : 
		//-----------------------------------------------------------------------------
		DWORD	GetAccumulationTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    
		///           
		/// \return    : 
		//-----------------------------------------------------------------------------
		DWORD	GetBeginAnalogRange();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    
		///           
		/// \return    : 
		//-----------------------------------------------------------------------------
		DWORD	GetEndAnalogRange();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    
		///           
		/// \return    : 
		//-----------------------------------------------------------------------------
		DWORD	GetResultDelayTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    
		///           
		/// \return    : 
		//-----------------------------------------------------------------------------
		DWORD	GetZeroPointValue();	

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF60xDevice::
		/// \brief    
		///           
		/// \return    : 
		//-----------------------------------------------------------------------------
		const RF60xPARAMS* GetParams() const;

		BOOL	HelloCmd();

		BOOL	CustomCmd(BYTE ucCommand, void* lpBuffer, WORD usBufferLength);

		/************************************************************************/
		/* Ethernet functions		                                            */
		/************************************************************************/
		BOOL	EthernetOpenPort(unsigned short nPort = 0);
		BOOL	EthernetSetTimeout(DWORD dwTimeout);
		BOOL	EthernetClosePort();

#ifdef RFDEVICE_FACTORY_API
		RF_customer_id	GetCustomerId();
		BOOL			SetCustomerId(const RF_customer_id wId);
#endif

	protected:
		LPRF60X_HANDLE_CONTEXT m_lphHandle;
		RF60xPARAMS m_params;	

		//void PopulateParams();
		BOOL ParamsRead();
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF60XDEVICE_INCLUDE
