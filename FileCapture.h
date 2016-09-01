#pragma once

/*
Author: Neil Kenny 

responible for opening stream with file and capturing stream
*/
#include "stdAfx.h"
#include <cv.h>
#include <highgui.h>
class FileCapture
{

private: 

	cv::VideoCapture captureObject;
public:
	FileCapture(void);
	~FileCapture(void);

	/**
	Opens file 
	@param path to file
	*/
	bool OpenFile(std::string filePath);

	/**
	Reads frame from file
	@param [in] opencv Matrix that will display the frame 
	*/
	bool Capture(cv::Mat &videoFrame);
	
};

