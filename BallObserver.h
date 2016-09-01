#pragma once

#include "stdAfx.h"
#include <vcclr.h>
#include "IBallObserver.h"
#include "IManagedBallObserver.h"

class BallObserver : public IBallObserver
{
public:

	BallObserver( IManagedBallObserver^ observer );

	/**
	 	Fire off a ball update to test the observer
	 */
	void test();

	virtual void onBallsUpdated( const std::vector<Ball>& balls );

private:

	/// Managed Ball Observer
	gcroot<IManagedBallObserver^> m_observer;
};


