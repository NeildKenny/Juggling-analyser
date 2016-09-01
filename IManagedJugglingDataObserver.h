#pragma once 

#include<vector>
#include "SHeightSiteswap.h"

#pragma managed

public interface class IManagedJugglingDataObserver
{	
	void JugglingDataUpdated( const std::vector<ThrowData> siteswapData );
};