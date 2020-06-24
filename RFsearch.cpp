/************************************************************************/
/*																		*/
/*	RF625_udp.cpp														*/
/*																		*/
/*	RFDevice sample program												*/
/*																		*/
/*	 Demonstrate how to:												*/
/*	 - Search RF625 over network										*/
/*	 - Read and display some user config from RF625						*/
/*	 - Connect(UDP) to the number of RF625								*/
/*	 - Read measurements(UDP) from RF625								*/
/*	 - Disconnect(UDP) the number of RF625								*/
/*																		*/
/************************************************************************/

#include "RFDevice_samples.h"
#include <iostream>
#include <vector>
#include <RF625Device.h>
#include <RFEthernetDetector.h>

using namespace std;

#define GETRESULT_ERROR_VALUE ((USHORT)0xffff)
#define MIN(a,b) (a<b ? a : b)
#define MEASURES_TO_DO 5
#define VALUES_TO_PRINT 4

int main(int argc, char *argv[])
{
	int nRF625;
	int i, j, k;
	vector<RFDevice::RF625Device *> vRF625;
	//	Buffer for maximal quantity of result points (X,Z * 1280 pts)
	float pPointsBuffer[RFDevice::RF625Device::ProfileValuesCount];
	USHORT nPoints;

	//	Initialize RFDevice
	RFDevice::Initialize();

	//	Create RFLanDetector object
	RFDevice::RFEthernetDetector ld;

	//	Execute search for device type 625 (RF625) for 3 seconds
	//	RF625 sends UDP information packet each 2 seconds so 3 seconds must be enough to catch all of them
	cout << "Searching..." << endl;
	nRF625 = ld.Search(625, 3);

	//	Now nRF625 holds a quantity of detected RF625
	cout << "Found " << nRF625 << " of RF625" << endl;

	//	Create list of RF625Device objects for all found devices
	for (i=0; i<nRF625; i++)
	{
		RFDevice::RF625Device *p = new RFDevice::RF625Device(ld[i]);
		if (p)
		{
			vRF625.push_back(p);
		}
		else
		{
			cout << "Failed to construct RF625Device #" << i << endl;
		}
	}
	nRF625 = vRF625.size();

	//	Sequentially connect(TCP) to each RF625 to read its UDP port number from user config block
	for (i=0; i<nRF625; i++)
	{
		if (FALSE == vRF625[i]->Connect())
		{
			cout << "Failed to Connect(TCP) to RF625Device #" << i << endl;
		}
		else
		{
			if (FALSE == vRF625[i]->ReadParams())
			{
				cout << "Failed to read user config of RF625Device #" << i << endl;
			}
			else
			{
				cout << "Read user config of RF625Device #" << i << endl;
				cout << "==========================================" << endl;
				cout << "   Serial Number: " << vRF625[i]->GetSerialNumber() << endl;
				cout << "TCP/IPv4 Address: " << vRF625[i]->GetHumanReadableActualDeviceIPAddress() << " (config value = " << vRF625[i]->GetHumanReadableDeviceIPAddress() << ")" << endl;
				cout << "UDP Host Address: " << vRF625[i]->GetHumanReadableHostIPAddress() << endl;
				cout << "   UDP Host Port: " << vRF625[i]->GetHostPortNumber() << endl;
				cout << "Ext.sync Enabled: " << ((vRF625[i]->GetExternalResultSyncEnabled() == TRUE) ? "YES" : "No") << endl;
				cout << "    Int.UDP Freq: " << (int)vRF625[i]->GetUDPFrequency() << endl;
				cout << "==========================================" << endl;
			}
		}
	}

	//	Sequentially disconnect(TCP) each RF625
	for (i=0; i<nRF625; i++)
	{
		if (FALSE == vRF625[i]->Disconnect())
		{
			cout << "Failed to Disconnect(TCP) RF625Device #" << i << endl;
		}
		else
		{
			cout << "Disconnected(TCP) RF625Device #" << i << endl;
		}
	}

	//	Sequentially connect(UDP) to each RF625
	for (i=0; i<nRF625; i++)
	{
		if (FALSE == vRF625[i]->UDPConnect())
		{
			cout << "Failed to Connect(UDP) to RF625Device #" << i << endl;
		}
		else
		{
			cout << "Connected(UDP) to RF625Device #" << i << endl;
		}
	}

	//	Sequentially get MEASURES_TO_DO measures from each RF625
	for (i=0; i<nRF625; i++)
	{
		cout << "RF625Device #" << i << ":" << endl;
		for (k=0; k<MEASURES_TO_DO; k++)
		{
			if (GETRESULT_ERROR_VALUE == vRF625[i]->UDPGetNormalizedResult(pPointsBuffer, &nPoints))
			{
				cout << "Failed to read measure (UDPGetResult timeout)" << endl;
			}
			else
			{
				//	Print first VALUES_TO_PRINT values
				cout << "[" << k << "] : " << nPoints << " points:" << endl << "  {";
				for (j=0; j<MIN(VALUES_TO_PRINT,nPoints); j++)
				{
					cout << pPointsBuffer[j*2] << "," << pPointsBuffer[j*2+1];
					if (j<MIN(VALUES_TO_PRINT-1,nPoints-1)) cout << "; ";
				}
				cout << "...}" << endl;
			}
		}
	}

	//	Sequentially disconnect(UDP) each RF625
	for (i=0; i<nRF625; i++)
	{
		if (FALSE == vRF625[i]->UDPDisconnect())
		{
			cout << "Failed to Disconnect(UDP) RF625Device #" << i << endl;
		}
		else
		{
			cout << "Disconnected(UDP) RF625Device #" << i << endl;
		}
	}

	//	Release memory
	while (!vRF625.empty())
	{
		delete vRF625.back();
		vRF625.pop_back();
	}

	//	Cleanup RFDevice
	RFDevice::Cleanup();

	//EXIT_CONSOLE

	return 0;
}
