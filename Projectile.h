#pragma once

/*
Author: Neil Kenny 

This class is the logic behind the projectile data

*/

#include "ProjectileMotion.h"

#include <time.h>       

class Projectile : public ProjectileMotion
{
public:
	Projectile(void);
	~Projectile(void);
	/**
	Derives objects projectile data given points and time
	@param [in]
		_ball: Ball object containing the data required 
				and to be updated
		t_msec: 
	*/
	void BallInMotion(Ball &_ball, double _baseHeight);

};

