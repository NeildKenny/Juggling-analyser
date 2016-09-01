#include "stdAfx.h"
#include "Morphology.h"


Morphology::Morphology(void)
{
}


Morphology::~Morphology(void)
{
}
 cv::Mat Morphology::erosion(cv::Mat source, int erosion_element, int erosion_size ){


	cv::Mat returnMat;
	int erosion_type; 
	if(erosion_element == 1){	
		erosion_type = cv::MORPH_RECT;
	}else if(erosion_element == 2){
		erosion_type = cv::MORPH_CROSS;
	}else if(erosion_element == 3){
		erosion_type = cv::MORPH_ELLIPSE;
	}

	cv::Mat Element = cv::getStructuringElement(erosion_type, cv::Size( 2*erosion_size + 1, 2*erosion_size + 1 ),
                                       cv::Point( erosion_size, erosion_size ));

	erode(source, returnMat, Element);
	return returnMat;

}

cv::Mat Morphology::dilation(cv::Mat source, int dilation_element, int dilation_size){
	

	cv::Mat return_mat;
	int dilation_type;
	if(dilation_element == 1){
		dilation_type = cv::MORPH_RECT;
	} else if(dilation_element ==  2){
		dilation_type = cv::MORPH_CROSS;
	} else if(dilation_element ==3){
		dilation_type = cv::MORPH_ELLIPSE;
	}

	cv::Mat element = cv::getStructuringElement(dilation_type,
                                       cv::Size( 2*dilation_size + 1, 2*dilation_size + 1 ),
                                       cv::Point( dilation_size, dilation_size ) );
	dilate(source, return_mat, element);
	return return_mat; 
}


void Morphology::applyGaussian(cv::Mat &filterMat){
	
	cv::GaussianBlur(filterMat, filterMat, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT);
	cv::imshow("Gauss", filterMat);

}

