#pragma once

#include <vector>

class Ball;

#pragma managed

public interface class IManagedBallObserver
{
	void BallsUpdated( const std::vector<Ball> balls );
};