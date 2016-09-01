#pragma once

#include "stdAfx.h"
#include <vcclr.h>
#include "IJugglingDataObserver.h"
#include "IManagedJugglingDataObserver.h"
#include "SHeightSiteswap.h"

class JugglingDataObserver: public IJugglingDataObserver
{
public:
	JugglingDataObserver( IManagedJugglingDataObserver^ observer );
	
	void test();

	virtual void onDataUpdated( const std::vector<ThrowData> &siteswapData );

private:

	gcroot<IManagedJugglingDataObserver^> m_observer;

};

