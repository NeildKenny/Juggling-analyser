#pragma once

/*
Author: Neil Kenny 

Applies morphological operation and filters to opencv matrixs in order to decrease noise

*/
#include <cv.h>
#include <highgui.h>
class Morphology
{
public:
	Morphology(void);
	~Morphology(void);

	/**
		applies erosion to image in order to decrease noise
	@param:
		source: Binary matrix  
		erosion_element: Choice of matrix structure to erode by
		erosion_size: Size of matrix to use
	@return eroded binary image
	*/
	cv::Mat erosion(cv::Mat source, int erosion_element, int erosion_size );
	/**
	applies dialation in order to help small objects
	@param:
		source: Binary image
		dilation_element: Choice of matrix structure to dilate by
		dilation_size: Size of matrix to use
	@return dilated binary image
	*/
	cv::Mat dilation(cv::Mat source, int dilation_element, int dilation_size);
	/*
		@param:
		matrix to be filtered
	*/
	void applyGaussian(cv::Mat &filterMat);

};