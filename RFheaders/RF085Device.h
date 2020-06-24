#ifndef RF085DEVICE_INCLUDE
#define RF085DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFEthernetDevice.h"
#include "RFTypeDefs.h"

namespace RFDevice {

	class RFDEVICE_API RF085Device : public RFEthernetDevice
	{
	public:
		RF085Device();
		RF085Device(LPCSTR szDeviceIPAddress);
		RF085Device(LPCSTR szDeviceIPAddress, LPCSTR szLocalIPAddress);
		~RF085Device();

		BOOL Connect();
		BOOL Connect(LPCSTR szDeviceIPAddress);
		BOOL Disconnect();

		BOOL GetStateOUT1(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateOUT2(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateOUT3(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateOUT4(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateOUT5(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateOUT6(BOOL bReadHardwareValue = FALSE);

		BOOL GetStateLED1(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateLED2(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateLED3(BOOL bReadHardwareValue = FALSE);

		BOOL SetStateOUT1(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateOUT2(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateOUT3(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateOUT4(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateOUT5(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateOUT6(BOOL state, BOOL bWriteHardwareValue = FALSE);

		BOOL SetStateLED1(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateLED2(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateLED3(BOOL state, BOOL bWriteHardwareValue = FALSE);

		BOOL ReadParamsOUT();
		BOOL ReadParamsLED();
		BOOL WriteParamsOUT();
		BOOL WriteParamsLED();

		RFDEVICE_DEPRECATED BOOL MotorEnable(BOOL bEnable, BYTE motor_id = 1);
		BOOL MotorMove(int nDistance, BYTE motor_id = 1);
		BOOL MotorGoHome(BYTE motor_id = 1);
		BOOL MotorStop(BYTE motor_id = 1);
		BOOL MotorReadStatus(BYTE motor_id = 1);
		BOOL MotorIsMoving(BOOL bReadHardwareStatus = FALSE, BYTE motor_id = 1);
		BOOL MotorAtHome(BOOL bReadHardwareStatus = FALSE, BYTE motor_id = 1);

		BOOL MotorReadParam(BYTE ucCmd, BYTE ucAddr, BYTE* lpucResult,BYTE motor_id = 1);
		BOOL MotorReadParams(BYTE motor_id = 1);
		BOOL MotorWriteParam(BYTE ucCmd, BYTE ucAddr, BYTE ucValue,BYTE motor_id = 1);
		BOOL MotorWriteParams(BYTE motor_id = 1);
		BOOL MotorRestoreParams(BYTE motor_id = 1);
		BOOL MotorFlushParams(BYTE motor_id = 1);

		//TODO: Move all cmds from QDPMotor
		WORD MotorGetSpeed(BOOL bReadHardwareValue = FALSE,BYTE motor_id = 1);
		WORD MotorGetACC(BOOL bReadHardwareValue = FALSE,BYTE motor_id = 1);
		WORD MotorGetDCC(BOOL bReadHardwareValue = FALSE,BYTE motor_id = 1);
		WORD MotorGetAlarm(BOOL bReadHardwareValue = FALSE,BYTE motor_id = 1);
		WORD MotorGetFSS(BOOL bReadHardwareValue = FALSE,BYTE motor_id = 1);

		BOOL MotorSetSpeed(WORD wSpeed, BOOL bWriteHardwareValue = FALSE,BYTE motor_id = 1);
		BOOL MotorSetACC(WORD wACC, BOOL bWriteHardwareValue = FALSE,BYTE motor_id = 1);
		BOOL MotorSetDCC(WORD wDCC, BOOL bWriteHardwareValue = FALSE,BYTE motor_id = 1);
		BOOL MotorSetAlarm(WORD wAlarm, BOOL bWriteHardwareValue = FALSE,BYTE motor_id = 1);
		BOOL MotorSetFSS(WORD wFSS, BOOL bWriteHardwareValue = FALSE,BYTE motor_id = 1);


	protected:
		RF085_PARAMETERS m_params;
		char* m_szDeviceIPAddress;
		char* m_szLocalIPAddress;

		BOOL PopulateParams();
		BOOL SetDeviceIPAddress(LPCSTR szDeviceIPAddress);
		BOOL SetLocalIPAddress(LPCSTR szLocalIPAddress);

		BOOL FlushSockRecv(int nDelay);

		SOCKET m_sockRecv;

	private:
		BYTE m_datagram[8];
		BYTE m_answer[8];

	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF085DEVICE_INCLUDE
