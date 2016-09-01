
/*
Author: Neil Kenny 

This class is used to capture and convert the data streams from the kinect
returning them as CV::mats to the desired class

*/
#include "OpenKinect.h"
#include <cv.h>
#include <highgui.h>
#define STREAM_TIMEOUT 2000


class KinectCapture : public OpenKinect
{

private:
	int currentStream;
	bool depthCaptured, colorCaptured;
	//openni::VideoFrameRef depthFrame, colorFrame; 
	uint64_t depthTimestamp, colorTimestamp;

	/**
	Captures colour frame from the kinect using openni and converts 
	it from an openni videoFrame to an opencv Matrix
	@return colour 
	*/
	cv::Mat KinectCaptureColor(void);
	/**
	Captures depth frame from the kinect using openni and converts 
	it from an openni videoFrame to an opencv Matrix
	@return colour 
	*/
	cv::Mat KinectCaptureDepth(void);


	openni::VideoFrameRef depthFrame, colorFrame; 
public:
	KinectCapture(void);
	~KinectCapture(void);
	
	
	/**
	Captures frames from the kinect
	@return vector of matrixs depth and RGB
	*/
	cv::vector<cv::Mat> CaptureFromKinect(void);
	


};

