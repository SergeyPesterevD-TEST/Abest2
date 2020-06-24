#ifndef RFDEVICEDEFS_INCLUDE
#define RFDEVICEDEFS_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef __linux__
#include <arpa/inet.h>
#include "linuxTypeDefs.h"
#endif
#include "serial.h"

namespace RFDevice {


	/************************************************************************/
	/* Ethernet Structures                                                       */
	/************************************************************************/
	//-----------------------------------------------------------------------------
	//  STRUCT  UDP_DEVINFOBLOCK_PC
	/// \brief    Structure to store Ethernet device related data collected during search.
	///
	/// \return   none
	//-----------------------------------------------------------------------------
#pragma pack(push, 1)
	typedef struct _UDP_DEVINFOBLOCK_PC {
		WORD				usDeviceType;
		BYTE				ucIP[4];
		BYTE				ucMAC[6];
		BYTE				ucInfo[256];
		_UDP_DEVINFOBLOCK_PC  *		pNext;
	}  UDP_DEVINFOBLOCK_PC, *LPUDP_DEVINFOBLOCK_PC;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _UDP_DEVINFOBLOCK {
		WORD				usDeviceType;
		BYTE				ucIP[4];
		BYTE				ucMAC[6];
		BYTE				ucInfo[256];
	}  UDP_DEVINFOBLOCK, *LPUDP_DEVINFOBLOCK;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF_COMMAND_PACKET {
		DWORD				ulCommand;
		DWORD				ulAttachSize;
		DWORD				ulOffset;
		DWORD				ulSize;
	}  RF_COMMAND_PACKET, *LPRF_COMMAND_PACKET;
#pragma pack(pop)

	/************************************************************************/
	/* RF620HS Structures                                                   */
	/************************************************************************/

/*
	UDP information packet
	256 bytes long
*/
#pragma pack(push, 1)
	typedef struct _RF620HS_INFO_
	{
		BYTE	ucCaps;					//	0	: 1
		BYTE	ucSerial[3];			//	1	: 3
		WORD	wBaseDistance;			//	4	: 2
		WORD	wMeasurementRange_Z;	//	6	: 2
		WORD	wMeasurementRange_X_SMR;//	8	: 2
		WORD	wMeasurementRange_X_EMR;//	10	: 2
		WORD	wDiscreteValue;			//	12	: 2
		WORD	wErrorValue;			//	14	: 2
		DWORD	dwFirmwareVersion;		//	16	: 4
		BYTE	ucLaserColor;			//  20	: 1
		DWORD	dwCoreAVersion;		//	21	: 4
		DWORD	dwCoreBVersion;		//	25	: 4
		DWORD	dwFPGAVersion;		//	29	: 4
		BYTE	ucReserved_1[167];		//  33 : 167
		BYTE	ucAnalogOut;		//  200 : 1
		BYTE	ucSyncChannels;		//  201 : 1
		BYTE	ucTCPConnected;		//  202 : 1
		BYTE	ucReserved_2[17];		//  203 : 17
		WORD	wUDPPort;			// 220 : 2
		WORD	wClientId;			// 222 : 2
		WORD	wTCPPort;			// 224 : 2
		WORD	w_int_time;			// 226 : 2
		WORD	w_image_vcc;			// 228 : 2
		WORD	w_image_acc;			// 230 : 2
		WORD	w_fpga_vcc;			// 232 : 2
		WORD	w_fpga_icc;			// 234 : 2
		WORD	w_total_vcc;			// 236 : 2
		WORD	w_total_icc;			// 238 : 2
		WORD	w_bf609_vcc;			// 240 : 2
		WORD	w_bf609_icc;			// 242 : 2
		WORD	w_ddr2_vcc;			// 244 : 2
		WORD	w_ddr2_icc;			// 246 : 2
		WORD	w_bf_temp_LOC;			// 248 : 2
		WORD	w_bf_temp_EXT;			// 250 : 2
		WORD	w_fpga_temp;			// 252 : 2
		WORD	w_air_temp;			// 254 : 2
	} RF620HS_INFO, *LPRF620HS_INFO;
#pragma pack(pop)

/*
	ModbusTCP parameters (part of RF620HS_PARAMETERS)
	24 bytes long
*/
#pragma pack(push, 1)
	typedef struct _RF620HS_MODBUS_INFO
	{
		WORD	wModbusDelay;
		WORD	wModbusProtocolID;
		BYTE	ucModbusUnitID;
		WORD	wModbusTransactionID1;
		WORD	wModbusLength1;
		BYTE	ucModbusFunction1;
		WORD	wModbusStartAddress1;
		WORD	wModbusRegCount1;
		WORD	wModbusTransactionID2;
		WORD	wModbusLength2;
		BYTE	ucModbusFunction2;
		WORD	wModbusStartAddress2;
		WORD	wModbusRegCount2;
		BYTE	ucModbusByteCount2;
	} RF620HS_MODBUS_INFO, *LPRF620HS_MODBUS_INFO;	// 24 bytes
#pragma pack(pop)

	#pragma pack(push, 1)
typedef struct _SHORT_USER_PARAMS_
{
	WORD what_todo;
	WORD laser_level_u8;   // 2
	DWORD exposure_time_u16;// 3
	WORD tcp_ip_address_u8[4];// 17
	WORD tcp_subnet_mask_u8[4];// 21
	WORD udp_ip_address_u8[4];// 25
	DWORD udp_port_u16;// 29
} SHORT_USER_PARAMS;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF625DHS_EMERGENCY_BLOCK_
	{
		DWORD	dwSerialNumber;	// 0 : 4
		WORD	dwCommand;		// 4 : 2
		unsigned int	value;
		SHORT_USER_PARAMS shortParams;
		BYTE	ucReserved[256-10-sizeof(SHORT_USER_PARAMS)];	// 6
	} RF625DHS_EMERGENCY_BLOCK, *LPRF625DHS_EMERGENCY_BLOCK;	// 256 bytes
#pragma pack(pop)

/*
	User parameters packet
	512 bytes long
*/
#pragma pack(push, 1)
	typedef struct _RF620HS_PARAMETERS_
	{
		BYTE	ucLaserLevel;			//	0	: 1
		WORD	wExposureTime;			//	2-1	: 2
		WORD	wProcessingTime;		//	4-3	: 2
		BYTE	ucWindowLeft;			//	5	: 1
		BYTE	ucWindowWidth;			//	6	: 1
		BYTE	ucWindowTop;			//	7	: 1
		BYTE	ucWindowHeight;			//	8	: 1
		BYTE	ucReserved1;			//	9	: 1
		short	sRotationAngle;			//	11-10	: 2
		WORD	wExtSyncSignal;			//	13-12	: 2
		BYTE	ucExtSyncDivider;		//	14	: 1
		BYTE	ucExtSyncDelay;			//	15	: 1
		BYTE	ucAnalogDotCount;		//	16	: 1
		BYTE	ucAnalogDotHold;		//	17	: 1
		BYTE	ucTCPAddress[4];			//	21-18	: 4
		BYTE	ucTCPSubnetMask[4];		//	25-22	: 4
		BYTE	ucUDPAddress[4];			//	29-26	: 4
		WORD	wUDPPort;				//	31-30	: 2
		BYTE	ucUDPFrequency;			//	32	: 1
		WORD	wTCPPort;				//	34-33	: 2
		BYTE	ucDHCP;					//	35	: 1
		BYTE	ucSyncInOutLine;		//	36	: 1
		BYTE	ucAutoExposure;			//	37	: 1
		BYTE	ucPixelBrightnessThres;	//	38	: 1
		BYTE	ucLegacyMode;			//	39	: 1
		BYTE	ucRawImageMode;			//	40	: 1
		BYTE	ucInterpolation;		//	41	: 1
		BYTE	ucModbusTcpEnabled;			//	42	: 1
		BYTE	ucModbusTcpAddr[4];		//	46-43	: 1
		WORD	wModbusTcpPort;			// 48-47	: 2
		RF620HS_MODBUS_INFO	ModbusInfo;	// 72-49	: 24
		WORD	wTCPDataPort;			// 74-73	: 2
		BYTE	ucReserved2[437];		//	511-75
	} RF620HS_PARAMETERS, *LPRF620HS_PARAMETERS;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF625DHS_PARAMETERS_
	{
		WORD	wConfigVersion;		// 0 : 2
		BYTE		ucLaserLevel;			// 2 : 1
		WORD	wExposureTime;		// 3 : 2
		WORD	wWindowTop;			//	5 : 2
		WORD	wWindowHeight;			//	7 : 2
		WORD	wExtSyncSignal;	// 9 : 2
		WORD	wExtSyncDivider;	// 11 : 2
		BYTE		ucTCPAddress[4];		// 13 : 4
		BYTE		ucTCPSubnetMask[4];		// 17 : 4
		BYTE		ucUDPAddress[4];		// 21 : 4
		WORD	wUDPPort;			// 25 : 2
		WORD	wUDPFrequency;		// 27 : 2
		WORD	wTCPPort;			// 29 : 2
		BYTE		ucAutoExposure;		// 31 : 1
		BYTE		ucPixelBrightnessThres;	// 32 : 1
		BYTE		ucDifBrightnessThres;	// 33 : 1
		BYTE		ucRawImageMode;			// 34 : 1
		BYTE		ucInterpolation;		// 35 : 1
		BYTE    	ucDHSEnable;			// 36 : 1
		BYTE    	ucAnalog;				// 37 : 1
		WORD		wSyncChannels;			// 38 : 2
		BYTE		ucMeasureSync;			// 40 : 1
		WORD		wDelaySync;				// 41 : 2
		BYTE		ucDivSync;				// 43 : 1
		WORD		wKeepTCPTime;			// 44 : 2
		BYTE		ucKeepTCP;				// 46 : 1
		BYTE		ucFilter;				// 47 : 1
		BYTE		ucSmooth;				// 48 : 1
		WORD		wFilterParam;			// 49 : 2
		WORD		wSmoothParam;			// 51 : 2
		BYTE		ucAP;					// 53 : 1
		BYTE		ucAH;					// 54 : 1
		BYTE		ucUDPStream;			// 55 : 1
		BYTE		ucAveraging;			// 56 : 1
		BYTE		ucDropCountersExt;		// 57 : 1
		BYTE		ucDropCountersInt;		// 58 : 1
		BYTE		invertXZ;				// 59 : 1
		BYTE		localSAPEnabled;		// 60 : 1

		BYTE		ucReserved[512-61];		// 61 : 0-padding
	} RF625DHS_PARAMETERS, *LPRF625DHS_PARAMETERS;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _con_DEBUG_REGISTERS_
	{
		unsigned short	PULSE[128];
		unsigned short  NUMBER_PIXEL;
		unsigned short  EXPOSURE;
	} con_DEBUG_REGISTERS, *LPcon_DEBUG_REGISTERS;
#pragma pack(pop)

	//-----------------------------------------------------------------------------
	//  STRUCT  COM_DESCRIPTOR
	/// \brief    Structure to store COM device related data.
	///
	/// \return   none
	//-----------------------------------------------------------------------------
	typedef struct _COM_DESCRIPTOR
	{
		char				szPort_Name[16];
		DWORD				dwSpeed;
		SerialPort*			hCOM;
		BYTE				ucDeviceType;
		BYTE				ucNetAddress;
		BYTE				ucRefs;
		_COM_DESCRIPTOR *	pNext;
	} COM_DESCRIPTOR, *LPCOM_DESCRIPTOR;

	typedef struct _RF60x_HANDLE_CONTEXT_
	{
		SOCKET 		sSendSocket;
		SOCKET 		sRecvSocket;
		sockaddr_in siRecvAddr;
		sockaddr_in siSendAddr;
		int			iSenderAddrSize;
	} RF60X_HANDLE_CONTEXT, *LPRF60X_HANDLE_CONTEXT;

#pragma pack(push, 1)
	typedef struct _RFCOM_HELLO_ANSWER_
	{
		BYTE	bDeviceType;
		BYTE	bDeviceModificaton;
		WORD	wDeviceSerial;
		WORD	wDeviceMaxDistance;
		WORD	wDeviceRange;
	} RFCOMHELLOANSWER, *LPRFCOMHELLOANSWER;
#pragma pack(pop)

#pragma pack(push, 1)
/*
	typedef struct _RF096_HELLO_SUBITEM_
	{
		WORD	w603Base;
		WORD	w603Range;
	} RF096HELLOSUBITEM, *LPRF096HELLOSUBITEM;

	typedef struct _RF096_HELLO_ANSWER_
	{
		BYTE	bDeviceType;
		BYTE	bDeviceRelease;
		WORD	wDeviceSerial;
		WORD	wAssemblyType;
		BYTE	wRecordLength;
		BYTE	wRecordsCountInPacket;
		WORD	wRecordsCountInFile;
		RF096HELLOSUBITEM	SubItems[15];
	} RF096HELLOANSWER, *LPRF096HELLOANSWER;
*/
	// 96 bytes
	typedef struct _RF096_HELLO_ANSWER_
	{
		BYTE	bDeviceType;
		BYTE	bDeviceRelease;
		BYTE	bDeviceSerial;
		WORD	wAssemblyType;
		WORD	wRecordLength;
		WORD	wRecordsCountInFile;
		WORD	wSensorSerial;
		WORD	wSensorBase;
		WORD	wSensorRange;
		BYTE	reserved[81];
	} RF096HELLOANSWER, *LPRF096HELLOANSWER;
#pragma pack(pop)

	typedef struct _RF096_PARAMS_
	{
		BYTE	bNetAddress;
		BYTE	bSensorOn;
		BYTE	bCW;
		BYTE	bUartBaud;
		BYTE	bModeRun;
		WORD	wSyncConst;
		DWORD	dwScanningSteps;
		DWORD	dwNumMeasuresOnTurn;
		WORD	wACC;
		WORD	wDEC;
		WORD	wMAX_SPEED;
		WORD	wMIN_SPEED;
		WORD	wFS_SPD;
		BYTE	bSTEP_MODE;
		WORD	wCONFIG;
		BYTE	bCANbaudRW;
		WORD	wStndIdentif;
		DWORD	dwExtIdentif;
		BYTE	bCANidentif;
		BYTE	bCANOn;
		BYTE	bCANnodeID;
		BYTE	R0calibr[32];
		BYTE	Destination_IP[4];
		BYTE	Gateway_IP[4];
		BYTE	Subnet_Mask[4];
		BYTE	Source_IP[4];
		BYTE	bLANmode;
		BYTE	bDeviceType;
		WORD	wSerialNumber;
		DWORD	dwMDESCRIPTOR_ARRAY;
	} RF096PARAMS, *LPRF096PARAMS;

	typedef struct _RF096_MEASURE_5_8_
	{
		DWORD	uCntStep;
		WORD	wInclinometer_MEASURE;
		WORD	wRF603_MEASURE;
	} RF096MEASURE5_8, *LPRF096MEASURE5_8;

	typedef struct _RF096_MEASURE_MAP_5_8_
	{
		RF096MEASURE5_8 measures[12];
	} RF096MEASUREMAP5_8, *LPRF096MEASUREMAP5_8;


	typedef struct _RF60x_PARAMS_
	{
		BOOL	LaserIsOn;
		BOOL	AnalogOutIsOn;
		BYTE	SampleAveragingControlByte;
		BYTE	NetAddress;
		DWORD	BaundRate;
		DWORD	AverageCount;
		DWORD	SamplingPeriod;
		DWORD	AccumulationTime;
		DWORD	ResultDelayTime;
		DWORD	ZeroPoint;
		DWORD	CanSpeed;
		DWORD	CanStdID;
		DWORD	CanExtID;
		BOOL	CanIdIsExt;
		BOOL	CanIsOn;
		BYTE	DestinationIP[4];
		BYTE	GateWayIP[4];
		BYTE	SubnetMask[4];
		BYTE	SourceIP[4];
		BOOL	EthIsOn;
		DWORD	BeginAnalogRange;
		DWORD	EndAnalogRange;
	} RF60xPARAMS, *LPRF60xPARAMS;

	typedef struct _RF60x_STREAM_VALUE_
	{
		WORD	wMeasure;
		BYTE	bStatus;
	} RF60xSTREAMVALUE, *LPRF60xSTREAMVALUE;

#pragma pack(push, 1)
	typedef struct _RF60x_UDP_VALUE_
	{
		WORD	wMeasure;
		BYTE	bStatus;
	} RF60xUDPVALUE, *LPRF60xUDPVALUE;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF60x_UDP_PACKET_
	{
		RF60xUDPVALUE	rf60xValArray[168];
		WORD	wDeviceSerial;
		WORD	wDeviceBaseDistance;
		WORD	wDeviceMeasureRange;
		BYTE	bPackCount;
		BYTE	bPacketControlSumm;
	} RF60xUDPPACKET, *LPRF60xUDPPACKET;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF60x_UDP_VALUE_N_
	{
		WORD	wMeasure;
		short	sNumber;
		BYTE	bStatus;
	} RF60xUDPVALUEN, *LPRF60xUDPVALUEN;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF60x_UDP_PACKET_N_
	{
		RF60xUDPVALUEN	rf60xValArray[100];
		WORD	wDeviceSerial;
		WORD	wDeviceBaseDistance;
		WORD	wDeviceMeasureRange;
		BYTE	bPackCount;
		BYTE	bPacketControlSumm;
		BYTE	bReserved[4];
	} RF60xUDPPACKETN, *LPRF60xUDPPACKETN;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF60xB_UDP_VALUE_
	{
		WORD	wMeasure;
		WORD	wExposition;
		BYTE	bStatus;
	} RF60xBUDPVALUE, *LPRF60xBUDPVALUE;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF60xB_UDP_PACKET_
	{
		RF60xBUDPVALUE	rf60xBValArray[100];
		WORD	wReserved;
		WORD	wReserved2;
		WORD	wDeviceSerial;
		WORD	wDeviceBaseDistance;
		WORD	wDeviceMeasureRange;
		BYTE	bPackCount;
		BYTE	bPacketControlSumm;
	} RF60xBUDPPACKET, *LPRF60xBUDPPACKET;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF60xHS_MEASURE_BLOCK_
	{
		WORD	wMeasure;
		BYTE	bStatus;
	} RF60xHSMEASUREBLOCK, *LPRF60xHSMEASUREBLOCK;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF60xHS_MEASURE_PACKET_
	{
		RF60xHSMEASUREBLOCK	rfbValues[168];
		//WORD	wBlocksCount;
		WORD	wDeviceSerial;
		WORD	wDeviceBaseDistance;
		WORD	wDeviceMeasureRange;
		BYTE	bPacketCount;
		BYTE	reserved;
		//BYTE	bPacketControlSumm;
		//WORD	wServiceInfo;

	} RF60xHSMEASUREPACKET, *LPRF60xHSMEASUREPACKET;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF65x_UDP_VALUE_
	{
		BYTE	bMeasure1;
		BYTE	bMeasure2;
		BYTE	bMeasure3;
		BYTE	bMeasure4;
		//unsigned long	dwMeasure;
		BYTE	bStatus;
	} RF65xUDPVALUE, *LPRF65xUDPVALUE;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF65x_UDP_PACKET_
	{

		BYTE	bDeviceType;
		BYTE	bPOVersion;
		WORD	wDeviceSerial;
		WORD	wDeviceBaseDistance;
		WORD	wDeviceMeasureRange;
		BYTE	bPacketMeasureQuantity;
		BYTE	bPackCount;
		RF65xUDPVALUE	rf65xValArray[5];

	} RF65xUDPPACKET, *LPRF65xUDPPACKET;
#pragma pack(pop)

	typedef struct _RF65x_PARAMS_
	{
		BOOL	MicrometerIsOn;
		BYTE	PriorityAndSyncroniseControlByte;
		BYTE	NetAddress;
		DWORD	BaundRate;
		DWORD	AverageCount;
		DWORD	SamplingPeriod;
		DWORD	BeginAnalogRange;
		DWORD	EndAnalogRange;
		DWORD	NominalValue;
		BYTE	ResultAndBoundaryControlByte;
		DWORD	ControlledBoundariesNumbers;
		BYTE	LowLimitByte;
		BYTE	UpLimitByte;
		BYTE	OutLogicControllByte;
		BYTE	SynchType;
		DWORD	RSSynch;
		DWORD	AveragingType;
		DWORD   ResultType;
		DWORD	ABoundaryNumber;
		DWORD	BBoundaryNumber;
		BOOL	AnalogSynch;
		DWORD    AnalogSynchNew;
		DWORD	ZeroPoint;
		DWORD	MinTolerance;
		DWORD	MaxTolerance;
		DWORD	EthSynch;
		DWORD	EthPackType;
		DWORD	EthPackMeasureQuantity;
		BYTE	EthDestinationtMAC[6];
		DWORD	SourceIP;
		DWORD   DestIP;
		DWORD	SubnetMask;
		DWORD	AnalogCalibrateLow;
		DWORD	AnalogCalibrateHigh;
		BYTE	Type;
		BYTE	Release;
		DWORD	BaseDist;
		DWORD	MeasureRange;
		DWORD	MatrixSize;


	} RF65xPARAMS, *LPRF65xPARAMS;

	typedef struct _RF25x_PARAMS_
	{
		BOOL	SensorIsOn;
		BYTE	SampleControlByte;
		BYTE	NetAddress;
		DWORD	BaundRate;
		DWORD	CoordStartPoint;
		DWORD	SamplingPeriod;
		DWORD	BeginAnalogRange;
		DWORD	EndAnalogRange;
		DWORD	AnalogOutScaling;
		DWORD	LowLimitOC;
		DWORD	UpLimitOC;
		DWORD	LogicOutPolarity;
	} RF25XPARAMS, *LPRF25XPARAMS;

#pragma pack(push, 1)
	typedef struct _RFQDPMOTOR_HELLO_ANSWER_
	{
		BYTE	bDeviceType;
		WORD	wDeviceSerial;
	} RFQDPMOTORHELLOANSWER, *LPRFQDPMOTORHELLOANSWER;
#pragma pack(pop)

	typedef struct _RFQDPMOTOR_PARAMS_
	{
		BYTE	NetAddress;
		BYTE	SysSW;
		DWORD	dwBaundRate;
		WORD	wMaxSpeed;
		DWORD	dwSpeed;
		BYTE	ucAccel;
		WORD	wAlarmFlags;
		WORD	wACC;
		WORD	wDCC;
		WORD	wFullStepSpeed;
		BYTE	ucStepMode;
		DWORD	dwConfig;
		BOOL	bHold;
	} RFQDPMOTORPARAMS, *LPRFQDPMOTORPARAMS;

	typedef struct _RF085_PARAMETERS_
	{
		BYTE	OUT1;
		BYTE	OUT2;
		BYTE	OUT3;
		BYTE	OUT4;
		BYTE	OUT5;
		BYTE	OUT6;
		BYTE	LED1;
		BYTE	LED2;
		BYTE	LED3;
		BOOL	bIsMoving;
		BOOL	bAtHome;
		// params
		WORD	wSpeed;
		WORD	wACC;
		WORD	wDCC;
		WORD	wAlarm;
		WORD	wFSS;
	} RF085_PARAMETERS, *LPRF085_PARAMETERS;

/*
#pragma pack(push,1)
	typedef struct _RF700_603PARAMS
	{
		unsigned short SerialNumber;
		unsigned short RangeValue;
	} RF700_603PARAMS, *LPRF700_603PARAMS;
#pragma pack(pop)
#pragma pack(push,1)
	typedef struct _RF700_PARAMETERS_
	{
		RF700_603PARAMS inner603Sensors[12];
		unsigned short innerTermoSN;
	} RF700_PARAMETERS, *LPRF700_PARAMETERS;
#pragma pack(pop)
#pragma pack(push,1)
	typedef struct _RF700_MEASURE_UDP_PACKET_
	{
		unsigned short measures[12];
	}	RF700MeasureUdpPacket, *LPRF700MeasureUdpPacket;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF700DEVINFOBLOCK_PC {
		unsigned short				usBoardType;
		unsigned char				ucBoardNum;
		unsigned char				ucSeatNBoardNum;
		unsigned short				usUARTBaudrate;
		unsigned short				usStreamSamplingPeriod;
		unsigned short				usSynchPulseDurHi;
		unsigned short				usSynchPulseDurLo;
		unsigned char				ucDstMAC[6];
		unsigned char				ucSrcMAC[6];
		unsigned char				ucDstIP[4];
		unsigned char				ucSrcIP[4];
		unsigned short				usUDPSendPort;
		unsigned short				usUDPRecvPort;
	}  RF700DEVINFOBLOCK_PC, *LPRF700DEVINFOBLOCK_PC;
#pragma pack(pop)
*/

//SPI supported baud rates
enum BaudRate
{
	BaudDefault		= 0,
	Baud2400		= 2400,
	Baud4800		= 4800,
	Baud9600		= 9600,
	Baud19200		= 19200,
	Baud38400		= 38400,
	Baud57600		= 57600,
	Baud115200		= 115200,
	Baud230400		= 230400,
	Baud460800		= 460800,
	Baud921600		= 921600
};

typedef	WORD	RF_customer_id;

#if (!defined _MSC_VER || _MSC_VER < 1600)
#define _In_
#define _Out_
#define _Out_bytecapcount_(x)
#define _In_bytecount_(x)
#define _In_opt_bytecount_(x)
#define _In_opt_
#endif

}//namespace

#if defined(__cplusplus)
}
#endif

#endif //RFDEVICEDEFS_INCLUDE

