#pragma once
#include <iostream>

/*
Author: Neil Kenny 

This class is responsible for some of the basic maths functions

*/

class MathStuff
{

private:
	
	double pi;

public:

	/**
	Default constructor
	Initialises Pi
	*/
	MathStuff(void);
	~MathStuff(void);

	/**
	Converts radians to degrees
	@param [in] theta in radians
	@return theta in degrees
	*/
	double RadiansToDegrees(double _theta);
	
	/**
	Gets speed in which object has traveled
	@param [in]
		_tmsec1: time at point one
		_tmsec2: time at point two
		_dist: Distance object has traveled
	@return: speed which the object has traveled across the screen

	*/
	double Velocity(double _dist, int _tmsec1, int _tmsec2);
	
	/**
	Gives distance between two points 
	@param [in] points object 
	@return distance between the aformentioned points
	*/
	double Distance(int _x1, int _y1, int _x2, int _y2);
	
	/**
	Calculate the angle of throw given the 2 points and deriving the third 
	@param [in] points of object
	@return angle in radians 
	*/
	double CalcTheta(int _x1, int _y1, int _x2, int _y2);


	/**
	Rounds number to the nearest decimal place
	@param [in] number to be rounded
	@return number rounded
	*/
	double round(double number);
	
};

