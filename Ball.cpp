#include "stdAfx.h"
#include "Ball.h"


Ball::Ball(void)
{

	x=0;
	y=0;
	z=0;
	lastX=0;
	lastY=0;
	lastZ=0;
	

	timeInMil=0;
	ballNum=0;

	velocity = 0.0;
	velocityTwo = 0.0;
	vVelocity = 0.0;
	hVelocity = 0.0;



	siteswap = 0 ;


	theta = 0.0;
	maxHeight = 0.0;
	flightTime = 0.0;
	catchTime = 0.0; 
	v0.velocity = 0.0;
	v1.velocity = 0.0;
}


Ball::~Ball(void)
{
}
/***********/

int Ball::getXPos(void) const{
	return x;
}

void Ball::setXPos(int _x){
	setLastX();
	x = _x;
}

/***********/

int Ball::getYPos(void) const{
	return y;
}

void Ball::setYPos(int _y){
	setLastY();
	y = _y;
}

/***********/

int Ball::getZPos(void) const{
	return z;
}

void Ball::setZPos(int _z){
	z = _z;
}

/***********/

int Ball::getLastX(void) const{
	return lastX;
}

void Ball::setLastX(){
	lastX = getXPos();
}

/***********/

int Ball::getLastY(void) const{
	return lastY;
}

void Ball::setLastY(){
	lastY = getYPos();
}

/***********/
int Ball::getLastZ(void) const{
	return lastZ;
}

void Ball::setLastZ(){
	lastZ = getZPos();
}


/***********/
Points Ball::getPoints(void) const{
	return currentPoint;
}

void Ball::setPoints(){
	Points pointObject;

	
	pointObject.xS = getXPos();
	pointObject.yS = getYPos();
	pointObject.zS = getZPos();
	pointObject.timeInMilS = getTime();
	
	ballPositions.push_back(pointObject);

}


/***********/
int Ball::getBallNum(void) const{
	return ballNum;
}



void Ball::setBallNum(int _ballNum){
	ballNum = _ballNum; 
}

/***********/
int Ball::getTime(void) const{
	return timeInMil;
}


void Ball::setTime(int _timeInMil){
	timeInMil = _timeInMil;

}

/***********/

double Ball::getVelocity(void) const{
	return velocity;
}

void Ball::setVelocity(double _v){
	velocity = _v;
}
/***********/

double Ball::getVelocityTwo(void) const{
	return velocity;
}

void Ball::setVelocityTwo(double _v2){
	velocityTwo = _v2;
}
/***********/

double Ball::getVVelocity(void) const{
	return vVelocity;
}


void Ball::setVVelocity(double _vv){
	vVelocity = _vv;
}

/***********/

double Ball::getHVelocity(void) const{
	return hVelocity;
}

void Ball::setHVelocity(double _hv){
	hVelocity = _hv;
}

/*********/

double Ball::getTheta() const{
	return theta;
}

void Ball::setTheta(double _theta){
	theta = _theta;
}
/*********/

void Ball::setFlightTime(double _flightTime){
	flightTime = _flightTime; 
}

double Ball::getFlightTime(void) const{
	return flightTime; 
}

/**********/

void Ball::setMaxHeight(double _maxHeight){
	maxHeight = _maxHeight;
}

double Ball::getMaxHeight() const{
	return maxHeight;
}

/**********/
void Ball::setCatchTime(double _catchTime){
	catchTime = _catchTime;
}

double Ball::getCatchTime(void) const{
	return catchTime;
}


/**********/
void Ball::setSiteswap(int _siteswap){

	siteswap = _siteswap;
}
int Ball::getSiteswap() const{
	return siteswap;
}