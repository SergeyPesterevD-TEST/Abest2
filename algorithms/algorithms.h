#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <list>
//#include "main.h"//// debug
#include "ap.h"
#include "interpolation.h"
#include "linalg.h"
#include "alglibinternal.h"
#include "statistics.h"
#include "pointn.h"
#include "Miniball.hpp"

#define MIN_POINTS_IN_BIN 100
#define MAX_AXIS_DIFFERENCE 2.0
#define	MAX_CENTERPOINT_RANGE 5.0

class Algorithms
{
public:
	Algorithms() {}
	static void Resample( std::multimap <double,PointN>& DataIn, std::map <double,PointN>& DataOut, int pts_rev);
	static int CalcCircleLSQ(std::map <double,PointN>& DataIn,PointN& centerPnt,double& Diam);
	static int CalcMEC(std::map <double,PointN>& DataIn,PointN& centerPnt,double& Diam);
	static int CalcMEC_CGAL(std::map <double,PointN>& DataIn,PointN& centerPnt,double& Diam);

	static int CalcEllipseLSQ(std::map <double,PointN>& DataIn, PointN& axisDiam,PointN& centerPnt,double &axisAngle);
	static int CalcXY0_Weiz(std::map <double,PointN>&DataIn,PointN& centerPnt); //bad
	static int CalcXY0_Wnd(std::map <double,PointN>&DataIn,std::vector <std::map <double,PointN>>& lndData,std::vector <PointN>& cloudCenters,std::vector<PointN>& Diams,double wndLen,double wndStdevMax,double binDif,int appType=1);// old pios style
	static int CalcXY0_Hist(std::map <double,PointN>&DataIn,std::vector <std::map <double,PointN>>& lndData,std::vector <PointN>& cloudCenters,double binDif);// old pios style
	static int CalcGaps(std::map <double,PointN>& DataIn, std::map <double,PointN>& DataInParsed, PointN& CenterPt,double diam,double minGap, std::vector <std::pair<PointN,PointN>>& WidthPts, std::vector<double> WidthData);
	static int CalcFlatsDiameters(std::map <double,PointN>& DataIn,std::map <double,PointN>& DataInParsed,std::map <double,PointN>& DataOut,double minGap,double centerEpsilon,PointN& DiamData);
	static int CompensateSelfEllipse(std::map <double,PointN>& DataIn,std::map <double,PointN>& DataOut,double binDif);


	static int CalibPoly(const alglib::real_1d_array &resX, const alglib::real_1d_array &resY, alglib::ae_int_t N, alglib::real_1d_array &a);
	static void ConvertMapToSet(const std::map<double, PointN> &map, std::set<PointN> &set);
};


#endif // ALGORITHMS_H




