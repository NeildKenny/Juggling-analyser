#pragma once
#include "stdAfx.h"
#include <cv.h>
#include <highgui.h>

/*
Author: Neil Kenny 

open and captures frames from camera fee

*/
class CameraCapture
{
private: 
	cv::VideoCapture captureObject;
	cv::Mat camImage;
public:

	/**
	Connects to webcam
	*/
	CameraCapture(void);
	~CameraCapture(void);

	/**
	Reads frame from webcam
	@returns opecv Matrix of captured frame
	*/
	cv::Mat Capture(void);
};

