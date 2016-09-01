#include "stdAfx.h"
#include "JugglingData.h"


JugglingData::JugglingData(void)
{

	
}


JugglingData::~JugglingData(void)
{
}


void JugglingData::setSiteswapData(Ball _ball){
	
	ThrowData ThrowDataObject;
			
	ThrowDataObject.siteswap = _ball.getSiteswap();
	ThrowDataObject.height = _ball.getMaxHeight();
	ThrowDataObject.flightTime = _ball.getFlightTime();
	ThrowDataObject.theta = _ball.getTheta();
	ThrowDataObject.z = _ball.getZPos();
	
	siteswapData[_ball.getSiteswap()].push_back(ThrowDataObject);
	
}

/**
	Why is it that this wont work in my mind?
	
*/
void JugglingData::setSiteswapData(std::vector<Ball> _balls){
	
	
	for(size_t i=0; i< _balls.size(); ++i){

		for(size_t j=0; j < _balls.size(); ++j){
			
			if(_balls[j].getSiteswap() == i){
				ThrowData ThrowDataObject;
			
				ThrowDataObject.siteswap = _balls[j].getSiteswap();
				ThrowDataObject.height = _balls[j].getMaxHeight();
				ThrowDataObject.flightTime = _balls[j].getFlightTime();
				ThrowDataObject.theta = _balls[j].getTheta();
				ThrowDataObject.z = _balls[j].getZPos();
				siteswapData[i].push_back(ThrowDataObject);
			}
		}
	}
}

std::vector<ThrowData> JugglingData::CompileData(void){
	compiledData.clear();
	for(size_t i = 0; i < siteswapData.size(); i++){
		
		for(size_t j =0; j < siteswapData[i].size(); j++){

				compiledData[i].height += siteswapData[i][j].height;
				compiledData[i].flightTime += siteswapData[i][j].flightTime; 
				compiledData[i].theta += siteswapData[i][j].theta;
				compiledData[i].z += siteswapData[i][j].z;
		}
		compiledData[i].height/=siteswapData[i].size();
		compiledData[i].flightTime/=siteswapData[i].size();
		compiledData[i].theta/=siteswapData[i].size();
		compiledData[i].z/=siteswapData[i].size();

	}
	return compiledData;
}