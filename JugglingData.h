#pragma once
#include<vector>
#include <map>
#include "Ball.h"
#include "SHeightSiteswap.h"
/*
Author: Neil Kenny 

This class is used compile the data from the throws

*/


class JugglingData
{

private:

	

public:
	JugglingData(void);
	~JugglingData(void);

	void setSiteswapData(std::vector<Ball> _balls);
	void setSiteswapData(Ball _ball);
	void getData(void);
	std::vector<ThrowData> CompileData(void);
	std::vector<ThrowData> compiledData;
	std::map<int, std::vector<ThrowData> > siteswapData;
};

