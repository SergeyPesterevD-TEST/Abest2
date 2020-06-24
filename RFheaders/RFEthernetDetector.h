/********************************************************************
	modified:	2013/04/16
	created:	2013/03/25
	filename: 	RFLanDetector.h
	author:		RIFTEK, LLC
	
	purpose:	Ethernet device detector class

	>>>>>>>>>>>><<<<<<<<<<<<<<
	>>>  INTERNAL VERSION  <<<
	>>>>>>>>>>>><<<<<<<<<<<<<<

*********************************************************************/

#ifndef RFLANDETECTOR_INCLUDE
#define RFLANDETECTOR_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFTypeDefs.h"

#define RFLanDetector RFEthernetDetector	// deprecated class name

namespace RFDevice {

	class RFDEVICE_API RFEthernetDetector
	{
	public:
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFEthernetDetector::RFEthernetDetector
		/// \brief    Default constructor of RFEthernetDetector object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RFEthernetDetector();
		RFEthernetDetector(const WORD wCustomPortNumber);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFEthernetDetector::~RFEthernetDetector
		/// \brief    Destructor of RFEthernetDetector object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		~RFEthernetDetector();

		BOOL SetCustomPortNumber(const WORD wCustomPortNumber);
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFEthernetDetector::Search
		/// \brief    Performs device search for timeout (seconds) period. Device type is specified with type argument (e.g., 620 for RF620 Series).
		///           
		/// \return   int : Number of detected devices.
		//-----------------------------------------------------------------------------
		int Search(USHORT type, int timeout);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFEthernetDetector::Clear
		/// \brief    Clears detected devices list. NOTE: Memory cleanup is done via destructor, you don't need to call Clear for this purpose.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		void Clear();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFEthernetDetector::GetSize
		/// \brief    Returns the number of items in detected devices list.
		///           
		/// \return   int : number of items.
		//-----------------------------------------------------------------------------
		int GetSize();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFEthernetDetector::GetDevBlock
		/// \brief    Returns a pointer to UDP_DEVINFOBLOCK_PC structure of device of specified index.
		///           
		/// \return   LPUDP_DEVINFOBLOCK_PC : a pointer.
		//-----------------------------------------------------------------------------
		LPUDP_DEVINFOBLOCK_PC GetDevBlock (const int index);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFEthernetDetector::operator []
		/// \brief    The same as GetDevBlock.
		///           
		/// \return   LPUDP_DEVINFOBLOCK_PC : a pointer.
		//-----------------------------------------------------------------------------
		LPUDP_DEVINFOBLOCK_PC operator[](const int index);


//////////////////////////////////////////////////////////////////////////
	private:
		BOOL UDP_Info_LookRecord(LPUDP_DEVINFOBLOCK, LPUDP_DEVINFOBLOCK_PC);

		LPUDP_DEVINFOBLOCK_PC m_lpDevBlock;
		int m_deviceCount;
		WORD m_portNumber;
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RFLANDETECTOR_INCLUDE
