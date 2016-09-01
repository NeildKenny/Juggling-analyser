#pragma once
/*
Author: Neil Kenny 

Tracking class used to detect and track objects from opencv frame

*/
#include <cv.h>
#include <vector>
#include <string>
#include "Ball.h"
#include "MathStuff.h"
#include "Morphology.h"
class Tracking: public MathStuff,public  Morphology
{
private :
	static const int MAX_OBJECTS = 400;
	static const int MIN_OBJECT_AREA = 20;
	static const int MAX_OBJECT_AREA= 100000;


 
	std::string intToString(int number);
	




public:
	Tracking(void);
	~Tracking(void);
	void DrawPath(std::vector<Ball> balls, cv::Mat &frame);
	
	/*
	Draws coordinates onto frame using high gui 
		balls: vector of balls containing coordinates to be draw 
		frame: frame to be drawn on
	*/
	void drawCoordinates(std::vector<Ball> balls, cv::Mat &frame);

	/*
	the main function in this class used for object detection through a thresholded cv::mat
	@param 
		binframe: Binary matrix
		cameraFrame: feed from camera 
		balls: vetor of ball object
		dilation type
		dilationsize 
		erosion type
		erosin size
	
	*/
	void Detect(cv::Mat &binFrame, cv::Mat &cameraFrame, std::vector<Ball> &balls, int _ero, int _dial, int _ero_size, int dila_size, int t_msec);
	/* Tracks object using nearest distance 
	@param balls: vector of ball objects to be compared to 
			x: coordinate of new position
			y: coordinate of new position
	@return element position
	*/
	int   Track(std::vector<Ball> balls, int x, int y);


	
	
};

