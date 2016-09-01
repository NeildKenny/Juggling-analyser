#include "stdAfx.h"
#include "Projectile.h"
#include "Siteswap.h"

Projectile::Projectile(void)
{
}


Projectile::~Projectile(void)
{
}


void Projectile::BallInMotion(Ball &_ball, double _baseHeight){

	for(int i = 0; i !=  _ball.ballPositions.size();i++){
		//std::cout << base[0] << std::endl;
		if( _ball.ballPositions[i].yS >= _ball.ballPositions[0].yS ){
			
			_ball.ballPositions.erase(_ball.ballPositions.begin(), _ball.ballPositions.begin()+i);
			i=0;
		}
		//std::cout << "Begin: " << base[0] << "    i  " << base[i] << std::endl;

	}

	int v0Element;
	for(size_t i = 1; i< _ball.ballPositions.size(); i++){

		/*
		if the position of the ball(i) > ball(0) and the time passed is greater than that+ 0.9 of a second then get the velocity of the ball and theta 
		
		*/
		
		if(_ball.ballPositions[0].yS >= _ball.ballPositions[i].yS &&
				_ball.ballPositions[i].timeInMilS >= _ball.ballPositions[0].timeInMilS+100 ){ 
			
			int t_msec = clock();
			
			double velocity = Velocity(
				(Distance(_ball.ballPositions[0].xS, _ball.ballPositions[0].yS, _ball.ballPositions[i].yS, _ball.ballPositions[i].xS )),
				_ball.ballPositions[0].timeInMilS, _ball.ballPositions[i].timeInMilS);
		
	
			if( velocity > _ball.v0.velocity  ){
				//_ball.setVelocity(velocity);
				_ball.v0.velocity = velocity;
				v0Element = i; 
				_ball.v0.time =(double) t_msec;
			}
			else if( _ball.v0.velocity > velocity && t_msec > _ball.v0.time  ){
				_ball.v1.velocity = velocity ;
				_ball.v1.time = (double) t_msec;
			}
			
			if(_ball.v0.velocity != NULL && _ball.v1.velocity != NULL){
				if( t_msec >= _ball.getCatchTime() ){

					double gravity;
					gravity = CalcGravity(_ball.v0.velocity, _ball.v1.velocity, _ball.v0.time,  _ball.v1.time);
					setGravity(gravity);

					//Only the angle of launch is required
					_ball.setTheta(CalcTheta(_ball.ballPositions[0].xS, _ball.ballPositions[0].yS, _ball.ballPositions[i].xS, _ball.ballPositions[i].yS));
					_ball.setMaxHeight(MaxHeight(_ball.v0.velocity, _ball.getTheta()));
					_ball.setFlightTime(FlightTime(_ball.v0.velocity, _ball.getTheta()));
					_ball.setVVelocity (VerticalVelocity(_ball.v0.velocity,_ball.getTheta()));
					_ball.setCatchTime(t_msec + _ball.getFlightTime());
					//t_msec = clock();
				
					//Balls flight time will only update when the ball is caught	
					//There are no siteswaps without a baseheight
					if(_baseHeight > 0.0 ){

						Siteswap siteswapObject  ;
						_ball.setSiteswap(siteswapObject.SiteswapValue(_baseHeight, _ball.getMaxHeight(), _ball.getTheta()));
					}
				}	
			}



		}
	}
}
