#include "stdAfx.h"
#include "BallObserver.h"

BallObserver::BallObserver( IManagedBallObserver^ observer ) :
m_observer( observer )
{}

void BallObserver::test()
{
	std::vector<Ball> balls;

	Ball ball1;
	ball1.setYPos( 100 );
	ball1.setBallNum( 1 );

	Ball ball2;
	ball2.setBallNum( 2 );
	ball2.setYPos( 200 );

	balls.push_back( ball1 );
	balls.push_back( ball2 );

	onBallsUpdated( balls );
}

void BallObserver::onBallsUpdated( const std::vector<Ball>& balls )
{
	m_observer->BallsUpdated( balls );
}