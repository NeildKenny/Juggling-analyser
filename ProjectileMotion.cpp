#include "stdAfx.h"
#include "ProjectileMotion.h"


ProjectileMotion::ProjectileMotion(void)
{
}


ProjectileMotion::~ProjectileMotion(void)
{
}
//wrong
double ProjectileMotion::MaxHeight(double velocity, double theta){
	
	double height;
	double _theta = sin(theta);
	_theta = RadiansToDegrees(_theta);
	theta = std::pow(_theta, 2);
	height = (std::pow(velocity,2))*theta/2*gravity;
	return height;
}


double ProjectileMotion::FlightTime( double velocity, double theta){
	
	double time;
	double _theta = sin(theta);
	_theta = RadiansToDegrees(_theta);
	return  time = (2*velocity)*(_theta)/gravity;
}


double ProjectileMotion::VerticalVelocity(double velocity, double flightTime){
	
	return velocity-(gravity*flightTime);
}



double ProjectileMotion::CalcGravity(double v1, double v2, int _time1, int _time2){
	double time1 = (double) _time1;
	double time2 = (double) _time2;
	gravity = (v1-v2);
	return gravity;

}

void ProjectileMotion::setGravity(double _gravity){
	gravity = _gravity;
}