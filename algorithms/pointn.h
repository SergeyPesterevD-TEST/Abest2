#ifndef POINTN_H
#define POINTN_H
#include <vector>
#include <initializer_list>
#include <limits>
#include <cmath>

/**
*	\brief base N dimension point class 
*/
class PointN
{

public:

    /*enumerator for dimension names*/
    enum POLAR
    {
        PHI=0,
        R=1
    };

    enum DECART
    {
        X=0,
        Y=1,
        Z=2
    };

    PointN() : polar_(false), id(0) {}
    /*constructor for a point in a form PointN({10,20,30}) creates a 3 dim point x=10 y=20 z=30 )*/
    PointN(std::initializer_list<double> list, bool polar)
        : container(list), polar_(polar), id(0) {}
    /*constructor for a point in a form PointN(N) creates a N dimensional point zeroed (not polar by default))*/
    PointN(unsigned int N, bool polar = false)
        : polar_(polar), id(0)
    {
        container.assign(N, 0);
    }
    /*get the point dimension*/
    unsigned int getDim() const {return container.size();}
    /*get the point type (polar or decart)*/
    bool getType() const {return polar_;}
    /*set the point type (polar or decart)*/
    void setType(bool polar)
    {
        if (polar == polar_) return;
        if (polar) //from decart to polar
        {
            auto _r = r();
            auto _phi = phi();
            container[R] = _r;
            container[PHI] = _phi;
        }
        else //from polar to decart
        {
            auto _x = x();
            auto _y = y();
            container[X] = _x;
            container[Y] = _y;
        }
        polar_=polar;
    }
    /*get x coord. calc if needed*/
    double x() const
    {
        if (container.empty()) return std::numeric_limits<double>::quiet_NaN();
        if (!polar_)
            return container[X];
        return container[R] * std::cos(container[PHI]);
    }
    /*get y coord. calc if needed*/
    double y() const
    {
        if (container.size() < 2) return std::numeric_limits<double>::quiet_NaN();
        if (!polar_)
            return container[Y];
        return container[R] * std::sin(container[PHI]);
    }
    /*get z coord. calc if needed*/
    double z() const
    {
        if (container.size() < 3) return std::numeric_limits<double>::quiet_NaN();
        return container[Z];
    }
    /*get r. calc if needed*/
    double r() const
    {
        if (container.size() < 2) return std::numeric_limits<double>::quiet_NaN();
        if (polar_)
            return container[R];
        return std::sqrt(container[X] * container[X] + container[Y] * container[Y]);
    }
    /*get phi (angle of polar point). calc if needed*/
    double phi() const
    {
        if (container.empty()) return std::numeric_limits<double>::quiet_NaN();
        if (polar_) return container[PHI];
        if (container.size() < 2) return std::numeric_limits<double>::quiet_NaN();
        auto angle = std::atan2(container[Y], container[X]);
        return angle > 0 ? angle : angle + 2 * M_PI;
    }
    /* get value of i dimensional.*/
    double get(unsigned int i)
    {
        if (i >= container.size()) return std::numeric_limits<double>::quiet_NaN();
        return container[i];

    }
    /*set x coord. calc if needed*/
    int setX(double _x)
    {
        if (!polar_)
        {
            if (container.empty())
                container.assign(1, 0);
            container[X] = _x;
        }
        else
        {
            if (container.size() < 2)
                return -1;
            auto _y = y();
            container[R] = std::sqrt(_x * _x + _y * _y);
            auto angle = std::atan2(_y, _x);
            container[PHI] = angle > 0 ? angle : angle + 2 * M_PI;
        }
    }
    /*set y coord. calc if needed*/
    int setY(double _y)
    {
        if (!polar_)
        {
            if (container.size() < 2)
                container.assign(2, 0);
            container[Y] = _y;
        }
        else
        {
            if (container.size() < 2)
                return -1;
            auto _x = x();
            container[R] = std::sqrt(_x * _x + _y * _y);
            auto angle = std::atan2(_y, _x);
            container[PHI] = angle > 0 ? angle : angle + 2 * M_PI;
        }
    }
    /*set z coord. calc if needed*/
    int setZ(double _z)
    {
        if (container.size() < 3)
            container.assign(3, 0);
        container[Z] = _z;
    }
    /*set r. calc if needed*/
    int setR(double _r)
    {
        if (polar_)
        {
            if (container.size() < 2)
                container.assign(2, 0);
            container[R] = _r;
        }
        else
        {
            if (container.size() < 2)
                return -1;
            auto _phi = phi();
            container[X] = _r * std::cos(_phi);
            container[Y] = _r * std::sin(_phi);
        }
    }
    /*set phi (angle of polar point). calc if needed*/
    int setPHI(double _phi)
    {
        if (polar_)
        {
            if (container.size() < 1)
                container.assign(1, 0);
            container[PHI] = _phi;
        }
        else
        {
            if (container.size() < 2)
                return -1;
            auto _r = r();
            container[X] = _r * std::cos(_phi);
            container[Y] = _r * std::sin(_phi);
        }
    }

    /**
*	\brief get point coordinates
*	Get point coordinates, if one of the coordinates is out of range (say we ask for Z for a two dimensional point) it will
*	be set to lowest double possible
*	\param[in]	coords	list of enums describing what coords to get {ccord_type::X,ccord_type::Y}
*	\param[out] values	list of references to variables where to put coordinates
*	\return Error:	1	one of dimensions is out of range
*/
    int get(std::initializer_list<DECART> coords ,std::initializer_list<double*> values ) const
    {
        int fl_bad=0;
        auto value = values.begin();
        for(auto coord = coords.begin(); coord != coords.end() && value != values.end(); ++coord, ++value)
        {
            if((*coord >= container.size()) || (*coord < 0))
            {
                fl_bad=1;
                **value = std::numeric_limits<double>::quiet_NaN();
            }
            else
            {
                if (!polar_)
                    **value = container[*coord];
                else
                {
                    switch (*coord)
                    {
                    case X: **value = x(); break;
                    case Y: **value = y(); break;
                    default: **value = container[*coord];
                    }
                }
            }
        }
        return fl_bad;
    }
    /**
*	\brief get point coordinates
*	Get point coordinates, if one of the coordinates is out of range (say we ask for Z for a two dimensional point) it will
*	be set to lowest double possible
*	\param[in]	coords	list of enums describing what coords to get {ccord_type::X,ccord_type::Y}
*	\param[out] values	list of references to variables where to put coordinates
*	\return Error:	1	one of dimensions is out of range
*/
    int get(std::initializer_list<POLAR> coords ,std::initializer_list<double*> values ) const
    {
        int fl_bad=0;
        auto value = values.begin();
        for(auto coord = coords.begin(); coord != coords.end() && value != values.end(); ++coord, ++value)
        {
            if((*coord >= container.size()) || (*coord < 0))
            {
                fl_bad=1;
                **value = std::numeric_limits<double>::quiet_NaN();
            }
            else
            {
                if (polar_)
                    **value = container[*coord];
                else
                {
                    switch (*coord)
                    {
                    case R: **value = r(); break;
                    case PHI: **value = phi(); break;
                    default: **value = container[*coord];
                    }
                }
            }
        }
        return fl_bad;
    }
    /**
*	\brief set point coordinates
*	\param[in]	coords	list of enums describing what coords to get {DECART::X,DECART::Y}
*	\param[out] values	list of variables containing coordinates
*	\return Error:	-1	requested dimension is larger then point dimension
*	\return Error:	-2	requested dimension does not exist
*/
    int set(std::initializer_list<DECART> coords, std::initializer_list <double> values )
    {
        if ((coords.size() != values.size()) || (coords.size() > container.size()))
            return -1;
        auto value = values.begin();
        double _x, _y;
        if (polar_)
        {
            _x = x();
            _y = y();
        }
        for(auto coord = coords.begin(); coord != coords.end(); ++coord, ++value)
        {
            if((*coord >= container.size()) || (*coord < 0)) return -2;
            if (!polar_)
                container[*coord]=*value;
            else
            {
                switch (*coord) {
                case X: setX(*value); break;
                case Y: setY(*value); break;
                default: container[*coord]=*value;
                }
            }
        }
    };
    /**
*	\brief set point coordinates
*	\param[in]	coords	list of enums describing what coords to get {POLAR::X,POLAR::Y}
*	\param[out] values	list of variables containing coordinates
*	\return Error:	-1	requested dimension is larger then point dimension
*	\return Error:	-2	requested dimension does not exist
*/
    int set(std::initializer_list<POLAR> coords, std::initializer_list <double> values )
    {
        if ((coords.size() != values.size()) || (coords.size() > container.size()))
            return -1;
        auto value = values.begin();
        for(auto coord = coords.begin(); coord != coords.end(); ++coord, ++value)
        {
            if((*coord >= container.size()) || (*coord < 0)) return -2;
            if (!polar_)
                container[*coord]=*value;
            else
            {
                switch (*coord) {
                case R: setR(*value); break;
                case PHI: setPHI(*value); break;
                default: container[*coord]=*value;
                }
            }
        }
    };
    /**
*	\brief set point coordinates
*	\param[in]	coords	list of enums describing what coords to get {ccord_type::X,ccord_type::Y}
*	\param[out] values	list of variables containing coordinates
*	\return Error:	-1	requested dimension is larger then point dimension
*	\return Error:	-2	requested dimension does not exist
*/
    int set(std::initializer_list <int> coords ,std::initializer_list <double> values )
    {
        if ((coords.size() != values.size()) || (coords.size() > container.size()))
            return -1;
        auto value = values.begin();
        for(auto coord = coords.begin(); coord != coords.end(); ++coord, ++value)
        {
            if((*coord >= container.size()) || (*coord < 0)) return -2;
            container[*coord]=*value;
        }
    }

    void setID(int val) { id = val; }
    int getID() const { return id; }

    PointN& operator += (const PointN & pnt)
    {
        if(container.size()>=pnt.container.size())
        {
            std::vector <double> thisPnt,thatPnt;
            thatPnt=pnt.container; // copy data to container ()
            thisPnt=this->container; // copy data to container ()

            if((this->polar_)) // if our point is in polar coordinates calculate it in orthogonal (also at least 2 dims are present)
            {
                thisPnt[X]=this->container[R]*std::cos(this->container[PHI]); //X
                thisPnt[Y]=this->container[R]*std::sin(this->container[PHI]); //Y
            }
            if((pnt.polar_)) // if rval point is in polar coordinates calculate it in orthogonal (also at least 2 dims are present)
            {
                thatPnt[X]=pnt.container[R]*std::cos(pnt.container[PHI]); //X
                thatPnt[Y]=pnt.container[R]*std::sin(pnt.container[PHI]); //Y
            }
            for(int i=0;i<thatPnt.size();i++) thisPnt[i]+=thatPnt[i];
            if(!this->polar_)
                this->container=thisPnt;
            else
            {
                this->container=thisPnt;
                this->container[PHI]=std::atan2(thisPnt[Y],thisPnt[X]); // PHI
                if(this->container[PHI]<0.0)
                    this->container[PHI]+=2*M_PI;
                this->container[R]=std::sqrt(thisPnt[X]*thisPnt[X]+thisPnt[Y]*thisPnt[Y]);
            }
        }
        return *this;
    }
    PointN& operator -= (const PointN & pnt)
    {
        if(container.size()>=pnt.container.size())
        {
            std::vector <double> thisPnt,thatPnt;
            thatPnt=pnt.container; // copy data to container ()
            thisPnt=this->container; // copy data to container ()

            if((this->polar_)) // if our point is in polar coordinates calculate it in orthogonal (also at least 2 dims are present)
            {
                thisPnt[X]=this->container[R]*std::cos(this->container[PHI]); //X
                thisPnt[Y]=this->container[R]*std::sin(this->container[PHI]); //Y
            }
            if((pnt.polar_)) // if rval point is in polar coordinates calculate it in orthogonal (also at least 2 dims are present)
            {
                thatPnt[X]=pnt.container[R]*std::cos(pnt.container[PHI]); //X
                thatPnt[Y]=pnt.container[R]*std::sin(pnt.container[PHI]); //Y
            }
            for(int i=0;i<thatPnt.size();i++) thisPnt[i]-=thatPnt[i];
            if(!this->polar_)
                this->container=thisPnt;
            else
            {
                this->container=thisPnt;
                this->container[PHI]=std::atan2(thisPnt[Y],thisPnt[X]); // PHI
                if(this->container[PHI]<0)
                    this->container[PHI]+=2*M_PI;
                this->container[R]=std::sqrt(thisPnt[X]*thisPnt[X]+thisPnt[Y]*thisPnt[Y]);
            }
        }
        return *this;
    }
    bool operator<(const PointN &p) const
    {
	return (this->phi() < p.phi());
    }


protected:
    std::vector <double> container;
    bool polar_;

    /* This parameter can be used for different reasons.
     * For example for determine sensor which measured this point,
     * or to assign a point to some group by some criteria.
     */
    int id;
};


#endif // POINTN_H
