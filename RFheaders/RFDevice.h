#ifndef RFDEVICE_INCLUDE
#define RFDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#if (defined _WIN32)
#define RFDEVICE_API __declspec(dllexport)
#else
#define RFDEVICE_API
#endif

#include <cstring>

#if defined _WIN32
#include <Windows.h>
#include <WinSock.h>
#pragma comment (lib,"ws2_32.lib")
#elif defined __linux__
#include <pthread.h>
#include <sys/socket.h>
#include "linuxTypeDefs.h"
#else
#error "Unsupported platform"
#endif

#ifdef __GNUC__
#define RFDEVICE_DEPRECATED __attribute__((deprecated))
#elif (defined _MSC_VER && _MSC_VER >= 1300)
#define RFDEVICE_DEPRECATED __declspec(deprecated)
#else
#define RFDEVICE_DEPRECATED
#endif

#define RF_ERR_NOERROR			(0)
#define RF_ERR_BADPARAMS		(-1)
#define RF_ERR_BADDEVITETYPE	(-2)
#define RF_ERR_SOCKETEEROR		(-3)
#define RF_ERR_CONNECTFAILED	(-4)
#define RF_ERR_NOTSUPPORTED		(-5)
#define RF_ERR_IOERROR			(-6)
#define RF_ERR_MALLOC			(-7)

namespace RFDevice {
	/************************************************************************/
	/* Initialize/Cleanup functions                                         */
	/************************************************************************/
	//-----------------------------------------------------------------------------
	//  FUNCTION  RFDevice::Initialize
	/// \brief    Global library initializations. Must be called once before using of most of library functions.
	///
	/// \return   BOOL : TRUE on success, FALSE on error.
	//-----------------------------------------------------------------------------
	BOOL RFDEVICE_API Initialize(void);
	//-----------------------------------------------------------------------------
	//  FUNCTION  RFDevice::Cleanup
	/// \brief    Must be called once before application exit.
	///
	/// \return   void
	//-----------------------------------------------------------------------------
	void RFDEVICE_API Cleanup(void);

	/************************************************************************/
	/* Return library version string										*/
	/************************************************************************/
	//-----------------------------------------------------------------------------
	//  FUNCTION  RFDevice::GetVersionString
	/// \brief    Get library name and version string.
	///
	/// \return   TRUE on success, FALSE otherwise
	//-----------------------------------------------------------------------------
	BOOL RFDEVICE_API GetVersion(LPCSTR lpszLibraryName, LPCSTR lpszLibraryVersionString);

#ifdef _M_X64
	int RFDEVICE_API RFDevice_GetLastError();
#else
	int RFDEVICE_API GetLastError();
#endif

	/************************************************************************/
	/* RFDevice Base class                                                  */
	/************************************************************************/
	class RFDEVICE_API RFDeviceObject
	{
	public:
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFDeviceObject::RFDeviceObject
		/// \brief    This is constructor of base RFDeviceObject object
		///
		/// \return   none
		//-----------------------------------------------------------------------------
		RFDeviceObject();
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFDeviceObject::~RFDeviceObject
		/// \brief    This is destructor of base RFDeviceObject object
		///
		/// \return   none
		//-----------------------------------------------------------------------------
		virtual ~RFDeviceObject();

	protected:
		DWORD m_DEV_ID;
	};

#if defined __linux__
	void InitializeCriticalSection(pthread_mutex_t* m);
	void EnterCriticalSection(pthread_mutex_t* m);
	void LeaveCriticalSection(pthread_mutex_t* m);
	void DeleteCriticalSection(pthread_mutex_t* m);
	#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
	//int WSAStartup(WORD versionRequested, void* wsaData);
	void WSACleanup();
	#define SOCKET int
	#define closesocket close
	DWORD GetTickCount();
#endif

}

#if defined(__cplusplus)
}
#endif

#endif //RFDEVICE_INCLUDE
