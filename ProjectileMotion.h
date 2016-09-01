#pragma once
/*
Author: Neil Kenny 

Contains equations relevant to projectile motin

*/
#include <math.h>
#include "Ball.h"
#include "MathStuff.h"
class ProjectileMotion : public MathStuff 
{

private:

	
public:
	ProjectileMotion(void);
	~ProjectileMotion(void);
	double gravity;
	
	
	/**
	Determines max height given angle of launch, velocity and gravity
	@param
		velocity: Object velocity
		theta: angle of launch
	@return: max height of the object
	
	*/
	double MaxHeight(double velocity, double theta);
	
	
	/**
	Determines flight time of object given launch, velocity and gravity
	@param
		velocity: Object velocity
		theta: angle of launch
	@return: flight time of the object
	
	*/
	double FlightTime( double velocity, double theta);
	
	/**
	Determines vertical velocity given angle of launch, velocity and gravity
	@param
		velocity: Object velocity
		theta: angle of launch
	@return:vertical velocity of the object
	
	*/
	double VerticalVelocity(double velocity, double theta);
	
	
	/**
	Setter for gravity
	@param [in] gravity 
	*/
	void setGravity(double _gravity);
	
	/**
	Calculates the change in velocity 
	*/
	double CalcGravity(double v1, double v2, int _time1, int _time2);
};

