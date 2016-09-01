#include "stdAfx.h"
#include "Siteswap.h"

Siteswap::Siteswap(void)
{
}


Siteswap::~Siteswap(void)
{
}

double Siteswap::BaseHeight(std::vector<double> base){
	
	double baseTotal = 0.0;
	double baseHeight = 0.0;
	for(std::vector<double>::iterator it = base.begin(); it != base.end();it++){
		baseTotal+=*it;
	}

	baseHeight = baseTotal/base.size();
	return baseHeight;

}

int Siteswap::SiteswapValue(double baseHeight, double maxHeight, double theta){

	double even = 0.34906585 ;

	double value = maxHeight/baseHeight;
	int roundedValue = (int)round(value);

	if(theta <= even && roundedValue % 2 == 0){
		return roundedValue;
	} else if(theta >  even && roundedValue % 2 ==0){
		return roundedValue+1;
	}else if(theta >=  even && roundedValue % 2 > 0 ){
		return roundedValue; 
	}else if (theta <  even && roundedValue % 2 > 0){
		return roundedValue+1;
	}else{
		return 1;
	}


}

double Siteswap::round(double number)
{
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}