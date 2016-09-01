#pragma once
#include <vector>

/*
Author: Neil Kenny 

Derives siteswap data

*/
class Siteswap
{
private:
	/**
	Rounds number to the nearest decimal place
	@param [in] number to be rounded
	@return number rounded
	*/
	double round(double number);
public:
	Siteswap(void);
	~Siteswap(void);
	/**
	Determines base height given average throw height
	@param [in] vector of maxheights thrown
	@return average height
	*/
	double BaseHeight(std::vector<double> base);
	/**
	Determines siteswap value given base height, throw height and angle of throw 
	@param [in]
		baseHeight: Average 3 ball throw height
		maxHeight: Throw height
		Theta: Angle of launch
	@return siteswap as integer
	*/
	
	int SiteswapValue(double baseHeight, double maxHeight, double theta);
};

