#ifndef RFQDPMOTORDEVICE_INCLUDE
#define RFQDPMOTORDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFSerialDevice.h"

namespace RFDevice {

	class RFDEVICE_API RFQDPMotorDevice : public RFSerialDevice
	{
	public:	
		RFQDPMotorDevice();
		~RFQDPMotorDevice();

		void BindNetworkAddress(BYTE ucAddress);
		BOOL HelloCmd();
		BOOL MoveTo(long nDeltaMove);
		BOOL SetMaxSpeed(WORD wSpeed);
		WORD GetMaxSpeed();
		BOOL SetAccel(BYTE ucAccel);
		BYTE GetAccel();
		BYTE GetSysSW();
		BOOL Stop();
		BOOL GoToZero();
		BYTE GetDeviceType();
		WORD GetSerialNumber();
		BOOL SetBaudRate(DWORD dwBaudRate);
		DWORD GetBaudRate();
		BOOL SetNetAddress(BYTE ucAddress);
		BYTE GetNetAddress();
		WORD GetAlarmFlags();
		BOOL SetAlarmFlags(WORD wFlags);
		WORD GetACC();
		WORD GetDCC();
		BOOL SetACC(WORD wACC);
		BOOL SetDCC(WORD wDCC);
		BOOL SetSpeed(DWORD dwSpeed);
		DWORD GetSpeed();
		BOOL SetFullStepSpeed(WORD wSpeed);
		WORD GetFullStepSpeed();
		BOOL SetStepMode(BYTE ucStepMode);
		BYTE GetStepMode();
		DWORD GetConfig();
		BOOL SetConfig(DWORD dwConfig);
		BOOL SetHold(BOOL bHold);
		BOOL GetHold();
		void ReadAllParams(LPRFQDPMOTORPARAMS lpParams);
		void SetAllParamsToDefaults();

	protected:
		RFQDPMOTORPARAMS m_params;
		RFQDPMOTORHELLOANSWER m_helloAnswer;

		BOOL ExecCommand(BYTE ucAddress, BYTE ucCmd, LPVOID lpParam, BYTE ucParamSize, LPVOID lpResult, BYTE ucResultSize);
		BOOL WriteParam(BYTE ucParamAddr, DWORD dwValue, const BYTE ucValueLength);
		BOOL ReadParam(BYTE ucParamAddr, LPVOID lpValue, const BYTE ucValueLength);
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RFQDPMOTORDEVICE_INCLUDE
