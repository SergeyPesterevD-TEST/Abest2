#ifndef FILTERS_H
#define FILTERS_H
#include <vector>
#include <map>
#include "pointn.h"
class Filter
{
	public:
	static int FIR_filter_96(std::map <double,PointN>& DataIn,std::map <double,PointN>& DataOut );
	static int FIR_filter_401(std::map <double,PointN>& DataIn,std::map <double,PointN>& DataOut );
	private:
	protected:
};

#endif // FILTERS_H
