#include "filters.h"
#include "fdacoefs.h"

/**
*	\brief apply lowpass FIR circular filter from fdacoefs length is 96
*   \param	Data	vector of data to filter
*	\return			 0 - ok
*	\return	Error:	-1 - length of data is less then filter length
*/
int  Filter::FIR_filter_96(std::map <double,PointN>& DataIn,std::map <double,PointN>& DataOut )
{
	std::vector<std::pair<double,double>> buff;
	double R;
	int lenD=DataIn.size();
	if(lenD<BL_96) return -1;
	//filter forward
	int i=0;
	for (std::map <double,PointN>::iterator itr=DataIn.begin();itr!=DataIn.end();++itr)
	{
		auto itr1=itr;
		buff.push_back({itr->first,0});
		for(int j=0;j<BL_96;j++)
		{
		  itr1->second.get({PointN::R},{&R});
		  buff.back().second+=R*B_96[BL_96-j-1];
		  if(itr1==DataIn.begin()) itr1=DataIn.end();
		  itr1--;
		}
	}
	//	 filter backward
	for (auto itr=buff.rbegin();itr!=buff.rend();++itr)
	{
		auto itr1=itr;
		R=0;
		for(int j=0;j<BL_96;j++)
		{
			R+=itr1->second*B_96[BL_96-j-1];
			if(itr1==buff.rbegin()) itr1=buff.rend();
			itr1--;
		}
		DataOut.insert({itr->first,{{itr->first,R},true}});
	}

	return 0;
}


/**
*	\brief apply lowpass FIR circular filter from fdacoefs length is 401
*   \param	Data	vector of data to filter
*	\return			 0 - ok
*	\return	Error:	-1 - length of data is less then filter length
*/
int  Filter::FIR_filter_401(std::map <double,PointN>& DataIn,std::map <double,PointN>& DataOut )
{
	std::vector<std::pair<double,double>> buff;
	double R;
	int lenD=DataIn.size();
	if(lenD<BL_401) return -1;
	//filter forward
	int i=0;
	for (std::map <double,PointN>::iterator itr=DataIn.begin();itr!=DataIn.end();++itr)
	{
		auto itr1=itr;
		buff.push_back({itr->first,0});
		for(int j=0;j<BL_401;j++)
		{
		  itr1->second.get({PointN::R},{&R});
		  buff.back().second+=R*B_401[BL_401-j-1];
		  if(itr1==DataIn.begin()) itr1=DataIn.end();
		  itr1--;
		}
	}
	//	 filter backward
	for (auto itr=buff.rbegin();itr!=buff.rend();++itr)
	{
		auto itr1=itr;
		R=0;
		for(int j=0;j<BL_401;j++)
		{
			R+=itr1->second*B_401[BL_401-j-1];
			if(itr1==buff.rbegin()) itr1=buff.rend();
			itr1--;
		}
		DataOut.insert({itr->first,{{itr->first,R},true}});
	}

	return 0;
}
