#include "stdAfx.h"
#include "MathStuff.h"


MathStuff::MathStuff(void)
{
 pi = 3.141592653589793;

}


MathStuff::~MathStuff(void)
{
}
double MathStuff::Distance(int _x1, int _y1, int _x2, int _y2){

	double distance;
	double x1 = (double)_x1;
	double y1 = (double)_y1;
	double x2 = (double)_x2;
	double y2 = (double)_y2;
	
	distance = std::sqrt( std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2) ); 

	return distance;
	
}

double MathStuff::Velocity(double _dist, int _tmsec1, int _tmsec2){

	double time, velocity;
	time = (double)( _tmsec2 - _tmsec1);
	return velocity = _dist/time;

}
double MathStuff::RadiansToDegrees(double _theta){
	return _theta = _theta*180/pi;
}


/*returns theta in rads*/
double MathStuff::CalcTheta(int _x1, int _y1, int _x2, int _y2){
	
	double theta;
	int x3 = _x1;
	int y3 = _y2;
	double hypotenuse = Distance(_x1,  _y1,  _x2,  _y2);
	double adjacent = Distance( _x1,  _y1,  x3,  y3);
	double opposite = Distance( x3,  y3,  _x2,  _y2);


	theta = opposite/hypotenuse;

	return theta;
}
 
double MathStuff::round(double number)
{
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}

	
