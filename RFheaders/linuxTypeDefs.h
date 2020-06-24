#ifndef RFDEVICE_LINUX_TYPEDEFS_H
#define RFDEVICE_LINUX_TYPEDEFS_H

typedef int BOOL;
typedef void* HANDLE;
typedef int SOCKET;
typedef unsigned char BYTE, *LPBYTE;
typedef unsigned short WORD, *LPWORD;
typedef unsigned int DWORD, *LPDWORD;
typedef char* LPSTR;
typedef const char* LPCSTR;
typedef unsigned short USHORT;
typedef struct sockaddr SOCKADDR;
#define Sleep(s) usleep(s*1000)
typedef int __int32;
typedef unsigned char UCHAR;
#define IN
#define OUT
#define SOCKET_ERROR (SOCKET)(-1)
#define INVALID_SOCKET (SOCKET)(-1)
#define TRUE 1
#define FALSE 0
#undef NULL
#define NULL 0
#define _O_CREAT O_CREAT
#define _O_WRONLY O_WRONLY
#define _O_BINARY 0x8000
#define _O_RDONLY O_RDONLY
#define _S_IWRITE S_IWRITE
typedef __int32 INT32, *PINT32;
typedef void VOID, *LPVOID;

#endif
