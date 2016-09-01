#pragma once

#include "stdAfx.h"
#include "Ball.h"
#include <vector>

class IBallObserver
{
	public:

		virtual void onBallsUpdated( const std::vector<Ball>& balls ) = 0;
};