#include "stdafx.h"
#include "JugglingDataObserver.h"


JugglingDataObserver::JugglingDataObserver( IManagedJugglingDataObserver^ observer ) : 
m_observer( observer )
{}

void JugglingDataObserver::test()
{
	
	std::vector<ThrowData> data;

	ThrowData throwData1;
	throwData1.siteswap=1;
	throwData1.z=300;
	throwData1.height=2000.00;
	throwData1.flightTime=900.00;
	throwData1.theta=0.93234;

	ThrowData throwData2;
	throwData2.siteswap=2;
	throwData2.z=400;
	throwData2.height=2345.00;
	throwData2.flightTime =251512.00;

	data.push_back( throwData1 );
	data.push_back( throwData2 );

	onDataUpdated( data );
}

void JugglingDataObserver::onDataUpdated( const std::vector<ThrowData> &siteswapData )
{
	m_observer->JugglingDataUpdated(siteswapData);

}