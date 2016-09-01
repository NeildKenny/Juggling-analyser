#pragma once 

#include "stdAfx.h"
#include "SHeightSiteswap.h"
#include <vector>

class IJugglingDataObserver
{
	public:

		virtual void onDataUpdated( const std::vector<ThrowData> &siteswapData ) = 0;
};