#pragma once
/*
Author: Neil Kenny 

This would be considered the main class, it is used to handle all of the video streams
and is the go between between the capture and tracking classes

*/
/*
References:
http://opencv-srf.blogspot.ie/2010/09/object-detection-using-color-seperation.html

*/

#include<cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include<string>
#include "KinectCapture.h"
#include "CameraCapture.h"
#include "FileCapture.h"
#include "Tracking.h"
#include "DatabaseHandler.h"
#include "Projectile.h"
#include "Siteswap.h"
#include "IBallObserver.h"
#include "IJugglingDataObserver.h"
#include "JugglingData.h"



class VideoHandler
{

private:

	//Variables
	int feed;
	static const int MAX_BALLS = 20;
	int t_msec;
	
	
	double baseHeight;
	bool getBase; 
	double baseCounter;
	double captureTime;
	
	std::string fileURI;

	//Frames

	cv::Mat actual;
	cv::Mat hsv;
	cv::Mat threshold;

	std::vector<IBallObserver*> mB_observers;
	std::vector<IJugglingDataObserver*> mT_observers; 
	
	//Vecs
	std::vector<Ball> balls; 
	std::vector<double> baseHeights;
	//Objects 
	
	
	Tracking trackObject;
	
	DatabaseHandler databaseHandlderObject;
	Siteswap siteswapObject;
	Projectile projectileObject;
	JugglingData jugglingDataObject;
	//Functions
	//Creates and manages stream from webcam and enables tracking
	void Webcam(void);
	//creates and manages stream from kinect and enables tracking 
	void Kinect(void);
	//creates and manages stream from file and enables tracking
	void File(void);

	//Thresholds image
	cv::Mat binaryImageCapture(cv::Mat actual);
	//thresholds but using static varibles for testing
	cv::Mat binaryImageCaptureConst(cv::Mat actual);

public:
	VideoHandler(void);
	~VideoHandler(void);
	
	//used to manage data feed on GUI
	void addBallObserver( IBallObserver* observer );
	void removeBallObserver( IBallObserver* observer );

	void addThrowObserver( IJugglingDataObserver* observer);
	void removeThrowObserver( IJugglingDataObserver* observer);
	//used in order to convert from a system::string to a std::string
	void MarshalString(System::String^ s, std::string& os);
	//sets uri for file capture stream
	void setFileUri(System::String^ _fileURI);

	//creates trackbar in order the threshold the object
	void createTrackBar(std::string trackBarName);
	//sets feed from gui for video stream
	void setFeed(int _feed);
	//informs the gui what feed is in use
	int getFeed(void);
	
	//manages which video stream is being used 
	void ManageFeeds();
	//Rotate image - http://opencv-code.com/quick-tips/how-to-rotate-image-in-opencv/
	void rotate(cv::Mat &src, cv::Mat &dst, int angle);
	std::vector<ThrowData> getJugglingdata(void);
	//sets up logic for base pattern
	void trackBasePattern(void );

};


