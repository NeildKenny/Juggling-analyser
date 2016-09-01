#pragma once

/*
Author: Neil Kenny 

Class responsible for managinb ball data

*/

#include "stdAfx.h"
#include <vector>
struct VelocityTime{
	double velocity;
	double time;
};
struct Points{
	int xS;
	int yS;
	int zS;
	int timeInMilS;
};
class Ball
{
	
private:

	int x;
	int y;
	int z;
	int lastX;
	int lastY;
	int lastZ;
	Points currentPoint;

	int timeInMil;
	int ballNum;
	int siteswap;


	double velocity;
	double velocityTwo;
	double vVelocity;
	double hVelocity;


	double theta;
	double maxHeight;
	double flightTime;
	double catchTime; 

	

public:
	Ball(void);
	~Ball(void);



	/*****************
	Start test functions
	******************/
	/**
	Setter and getter for ball coordinates required for testing for testing
	@param [in/out] previous ball coordinates
	*/
	void setLastX();
	void setLastY();
	void setLastZ();
	
	int getLastX(void) const;
	int getLastY(void) const;
	int getLastZ(void) const;
	/**
	Setter and getter for object speeds 
	@param [in/out] ball coordinates
	*/
	void setVelocity(double _v);
	void setVelocityTwo(double _v2);

	double getVelocity(void) const;
	double getVelocityTwo(void) const;

	/*****************
	End test functions
	******************/
	
	/**
	Setter and getter and getters for ball coordinates 
	@param [in/out]  respective ball coordinates
	*/
	void setXPos(int _x);
	void setYPos(int _y);
	void setZPos(int _z);

	int getXPos(void) const;
	int getYPos(void) const;
	int getZPos(void) const;
	/**
	Setter and getter for object horizontal velocity 
	@param [in/out] object horizontal velocity
	*/
	void setHVelocity(double _hv);
	double getHVelocity(void) const;

	/**
	Setter and getter for object horizontal velocity 
	@param [in/out] object vertical velocity
	*/
	void setVVelocity(double _vv);
	double getVVelocity(void) const;
	/**
	Setter and getter for object detection time
	@param [in/out] object detection time in milliseconds
	*/
	void setTime(int _timeInMil);
	int getTime(void) const;
	/**
	Setter and getter for object number to allow user to keep track of object in stream
	@param [in/out] object number
	*/
	void setBallNum(int _ballNum);
	int getBallNum(void) const;
	/**
	Setter and getter for object launch angle
	@param [in/out] object launch angle
	*/
	void setTheta(double _theta);
	double getTheta(void) const;
	/**
	Setter and getter for object max height required to allow us to determine siteswap of object
	@param [in/out] object max height of object
	*/
	void setMaxHeight(double _maxHeight);
	double getMaxHeight(void) const;
	/**
	Setter and getter for object flight time of object, allows us to determine when the object is caught 
	@param [in/out] object flight time of object
	*/
	void setFlightTime(double _flightTime);
	double getFlightTime(void) const;
	/**
	Setter and getter for when the object will be caught by user
	@param [in/out] object catch time of object
	*/
	void setCatchTime(double _catchTime);
	double getCatchTime(void) const;
	
	/**
	Setter and getter for the siteswap of the thrown object
	@param [in/out] objects siteswap
	*/
	void setSiteswap(int _siteswap);
	int getSiteswap(void) const;
	/**
	Getter for struct of  ball points and detection time
	@param [out] structure containing balls last points and time
	*/
	Points getPoints(void) const;
	/**
	Setter for struct of  ball points and detection time
	uses the internal getter functions to obtain points and time
	*/
	void setPoints(void);
	
	/**
	Vector containing all the point which the object has been at  set by setPoints()
	*/
	std::vector<Points> ballPositions;

	
	/**
	struct objects initial velocity 
	*/
	VelocityTime v0; 
	
	/**
	struct objects second velocity 
	*/
	VelocityTime v1;

	
	
};

